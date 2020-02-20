package kim.hsl.ffmpeg;

/**
 * Java 层与 Native 层交互 接口
 */
public class Player {

    // 加载动态库
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * 要播放的视频文件或直播地址
     */
    private String dataSource;

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
     * 释放资源
     */
    public void release(){

    }



}
