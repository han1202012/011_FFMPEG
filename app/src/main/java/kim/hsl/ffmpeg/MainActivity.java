package kim.hsl.ffmpeg;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {


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

        //这个是香港卫视直播地址
        player.setDataSource("rtmp://live.hkstv.hk.lxdns.com/live/hks");

        //设置视频显示组件
        player.setSurfaceView(surfaceView);

    }

    /**
     * 播放
     * @param view
     */
    public void play(View view) {
        player.prepare();
    }
}
