package kim.hsl.ffmpeg;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

    private static final String TAG = "FFMPEG";

    /**
     * 视频显示组件
     */
    private SurfaceView surfaceView;

    /**
     * FFMPEG 播放器
     */
    private Player player;

    /**
     * 播放进度条
     */
    private SeekBar seekBar;

    /**
     * 需要获取的权限列表
     */
    private String[] permissions = new String[]{
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.INTERNET,
            Manifest.permission.MODIFY_AUDIO_SETTINGS,
            Manifest.permission.RECORD_AUDIO
    };

    /**
     * 动态申请权限的请求码
     */
    private static final int PERMISSION_REQUEST_CODE = 888;

    /**
     * 动态申请权限
     */
    @RequiresApi(api = Build.VERSION_CODES.M)
    private void initPermissions() {
        if (isLacksPermission()) {
            //动态申请权限 , 第二参数是请求吗
            requestPermissions(permissions, PERMISSION_REQUEST_CODE);
        }
    }

    /**
     * 判断是否有 permissions 中的权限
     * @return
     */
    @RequiresApi(api = Build.VERSION_CODES.M)
    public boolean isLacksPermission() {
        for (String permission : permissions) {
            if(checkSelfPermission(permission) != PackageManager.PERMISSION_GRANTED){
                return true;
            }
        }
        return false;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode){
            case PERMISSION_REQUEST_CODE:
                if (grantResults.length > 0) {
                    for(int i = 0; i < grantResults.length; i++){
                        if(grantResults[i] != PackageManager.PERMISSION_GRANTED){
                            Toast.makeText(this,"权限为",Toast.LENGTH_SHORT).show();
                            return;
                        }
                    }
                }
                break;
        }
    }


    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //全屏
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);

        setContentView(R.layout.activity_main);

        surfaceView = findViewById(R.id.surface_view);
        seekBar = findViewById(R.id.seekBar);

        //创建播放器
        player = new Player();

        //设置视频显示组件
        player.setSurfaceView(surfaceView);

        /*
            RTSP协议直播源
            大熊兔（点播）：rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov   ( 不可用 )
            RTMP协议直播源
            大熊兔（点播）：rtmp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov   ( 不可用 )

            湖南卫视：rtmp://58.200.131.2:1935/livetv/hunantv    ( 可用 )
            广西卫视 ：rtmp://58.200.131.2:1935/livetv/gxtv
            广东卫视：rtmp://58.200.131.2:1935/livetv/gdtv
            东方卫视：rtmp://58.200.131.2:1935/livetv/dftv 
        */

        //这个是香港卫视直播地址 ( 不能用 )
        //player.setDataSource("rtmp://live.hkstv.hk.lxdns.com/live/hks");

        //这是湖南卫视的直播地址
        //player.setDataSource("rtmp://58.200.131.2:1935/livetv/hunantv");
        //player.setDataSource("/sdcard/game.mp4");

        player.setOnPrepareListener(new Player.OnPrepareListener() {
            @Override
            public void onPrepare() {
                //获取视频播放时长
                final int duration = player.getDuration();
                Log.i(TAG, "准备完毕 , 视频时长 : " + duration);

                //注意本回调是在 NDK 线程中执行的 , 如果想要更新 UI , 必须在主线程中执行
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        //如果视频时长为 0 , 说明是直播流 , 不显示进度条
                        if(duration == 0){
                            seekBar.setVisibility(View.GONE);
                        }else {
                            //如果视频时长大于 0, 说明是视频 , 显示进度条
                            seekBar.setVisibility(View.VISIBLE);
                        }
                    }
                });

                //开始播放
                player.start();
            }
        });

        // 初始化权限
        initPermissions();

        player.setOnProgressListener(new Player.OnProgressListener() {
            @Override
            public void onProgress(final int progress) {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        //获取视频时长
                        final float duration = player.getDuration();
                        //更新进度 计算比例
                        seekBar.setProgress((int) (progress * 100F / duration));
                    }
                });
            }
        });

        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                //此处跳转播放
                int progress = player.getDuration() * seekBar.getProgress() / 100;
                //进度调整
                player.seek(progress);
            }
        });
    }
    /**
     * 播放
     * @param view
     */
    public void play(View view) {
        switch (view.getId()){
            case R.id.playNativeVideo :
                player.setDataSource("/sdcard/game.mp4");
                break;
            case R.id.playVedioStream :
                player.setDataSource("rtmp://58.200.131.2:1935/livetv/hunantv");
                break;
        }
        player.prepare();
    }

    /**
     * 停止播放
     * @param view
     */
    public void stop(View view) {
        player.stop();
    }
}
