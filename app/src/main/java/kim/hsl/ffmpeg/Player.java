package kim.hsl.ffmpeg;

import android.util.Log;
import android.view.Surface;
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

    /**
     * 准备回调接口
     */
    private OnPrepareListener onPrepareListener;

    /**
     * 进度条回调接口
     */
    private OnProgressListener onProgressListener;

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

        //调用 Native 的本地方法
        native_start();

    }

    /**
     * 停止播放
     */
    public void stop(){
        native_stop();
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

        //释放资源
        native_release();

    }


    /**
     * C++ 层错误回调函数
     * @param errorCode
     */
    public void onError(int errorCode){
        Log.i(TAG, "出现错误 错误码 : " + errorCode);
    }

    /**
     * C++ 中 prepare 时回调该方法
     */
    public void onPrepare(){

        Log.i(TAG, "准备完毕 onPrepare");

        if(onPrepareListener != null){
            onPrepareListener.onPrepare();
        }
    }

    /**
     * C++ 中 进度更新 时回调该方法
     *
     * @param progress
     */
    public void onProgress(int progress) {
        if (null != onProgressListener) {
            onProgressListener.onProgress(progress);
        }
    }

    /**
     * 设置准备回调接口
     * @param onPrepareListener
     */
    public void setOnPrepareListener(OnPrepareListener onPrepareListener){
        this.onPrepareListener = onPrepareListener;
    }

    /**
     * 设置进度条回调接口
     * @param onProgressListener
     */
    public void setOnProgressListener(OnProgressListener onProgressListener) {
        this.onProgressListener = onProgressListener;
    }

    /**
     * 定义准备回调接口
     */
    public interface OnPrepareListener{
        void onPrepare();
    }

    /**
     * 定义进度条回调接口
     */
    public interface OnProgressListener {
        void onProgress(int progress);
    }


    public SurfaceView getSurfaceView() {
        return surfaceView;
    }

    public void setSurfaceView(SurfaceView surfaceView) {

        //防止注册多次
        if(this.surfaceHolder != null){
            this.surfaceHolder.removeCallback(this);
        }

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

        //将 Surface 传到 Native 层 , 在 Native 层绘制图像
        native_set_surface(holder.getSurface());

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        //画布销毁
    }

    /**
     * 获取视频的播放时长
     * 如果是直播流 , 获取的时间是 0
     * 如果是视频文件 , 获取的是大于 0 的时间
     * @return
     */
    public int getDuration(){
        return native_getDuration();
    }

    /**
     * 主界面调用播放器跳转播放
     * @param progress
     */
    public void seek(final int progress) {
        new Thread() {
            @Override
            public void run() {
                native_seek(progress);
            }
        }.start();
    }

    /**
     * 播放器准备
     * @param dataSource
     */
    native void native_prepare(String dataSource);

    /**
     * 播放器开始播放
     */
    native void native_start();

    /**
     * 播放器停止播放
     */
    native void native_stop();

    /**
     * 释放资源
     */
    native void native_release();

    /**
     * 将 Surface 画布传递到 Native 层
     * @param surface
     */
    native void native_set_surface(Surface surface);

    /**
     * 获取视频长度
     * @return
     */
    private native int native_getDuration();

    /**
     * Native 层开始
     * @param progress
     */
    private native void native_seek(int progress);

}
