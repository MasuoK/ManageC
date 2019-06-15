public class TemperatureInfo{
    String day; //日付(年月日)
    float high; //最高気温
    float low;  //最低気温
    float ave;  //平均気温

    protected TemperatureInfo(String iday, float ihigh, float ilow, float iave){
        this.day = iday;
        this.high = ihigh;
        this.low = ilow;
        this.ave = iave;
    }
   
    public String getDay(){
        return this.day;
    }
    public float getHigh(){
        return this.high;
    }
    public float getLow(){
        return this.low;
    }    
    public float getAve(){
        return this.ave;
    }
}