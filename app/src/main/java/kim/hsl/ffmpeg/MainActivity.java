package kim.hsl.ffmpeg;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "FFMPEG";

    /**
     * 视频显示组件
     */
    private SurfaceView surfaceView;

    /**
     * FFMPEG 播放器
     */
    private Player player;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        surfaceView = findViewById(R.id.surface_view);

        //创建播放器
        player = new Player();

        //设置视频显示组件
        player.setSurfaceView(surfaceView);

        /*
        RTSP协议直播源

        大熊兔（点播）：rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov

        RTMP协议直播源

        大熊兔（点播）：rtmp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov

        湖南卫视：rtmp://58.200.131.2:1935/livetv/hunantv

         广西卫视 ：rtmp://58.200.131.2:1935/livetv/gxtv


        广东卫视：rtmp://58.200.131.2:1935/livetv/gdtv


        东方卫视：rtmp://58.200.131.2:1935/livetv/dftv 
        */

        //这个是香港卫视直播地址
        //player.setDataSource("rtmp://live.hkstv.hk.lxdns.com/live/hks");
        player.setDataSource("rtmp://58.200.131.2:1935/livetv/hunantv");
        //player.setDataSource("rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov");

        player.setOnPrepareListener(new Player.OnPrepareListener() {
            @Override
            public void onPrepare() {
                Log.i(TAG, "准备完毕");
            }
        });

    }

    /**
     * 播放
     * @param view
     */
    public void play(View view) {
        player.prepare();
    }
}
