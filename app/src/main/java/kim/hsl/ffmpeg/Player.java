package kim.hsl.ffmpeg;

import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * Java 层与 Native 层交互 接口
 */
public class Player implements SurfaceHolder.Callback {

    private static final String TAG = "Player";

    // 加载动态库
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * 要播放的视频文件或直播地址
     */
    private String dataSource;

    /**
     * 视频显示组件
     */
    private SurfaceView surfaceView;

    /**
     * 控制 Surface 画布接口
     */
    private SurfaceHolder surfaceHolder;

    public String getDataSource() {
        return dataSource;
    }

    public void setDataSource(String dataSource) {
        this.dataSource = dataSource;
    }

    /**
     * 开始播放
     */
    public void start(){

    }

    /**
     * 停止播放
     */
    public void stop(){

    }


    /**
     * 准备播放的视频
     *
     * 执行的工作 :
     *      1 .
     */
    public void prepare() {

        //调用 Native 层的 FFMPEG 来实现视频播放的准备工作
        native_prepare(dataSource);

    }

    /**
     * 释放资源
     */
    public void release(){

        //防止内存泄漏 , 移除监听
        surfaceHolder.removeCallback(this);

    }


    public void onError(int errorCode){
        Log.i(TAG, "出现错误 错误码 : " + errorCode);
    }


    public SurfaceView getSurfaceView() {
        return surfaceView;
    }

    public void setSurfaceView(SurfaceView surfaceView) {
        this.surfaceView = surfaceView;

        //监听获取画布
        this.surfaceHolder = this.surfaceView.getHolder();
        surfaceHolder.addCallback(this);
    }


    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        //画布创建


    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        //画布改变 , 横竖屏切换 , 按下 Home 键 , 按下菜单键


    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        //画布销毁


    }

    native void native_prepare(String dataSource);


}
