public class TemperatureInfo{
    String day; //日付(年月日)
    float high; //最高気温
    float low;  //最低気温
    float ave;  //平均気温

    protected TemperatureComparator(String day, float high, float low, float ave){
        this.day = day;
        this.high = high;
        this.low = low;
        this.ave = ave;
    }
   
    public String getDay(){
        return this.day;
    }
    public int getHigh(){
        return this.high;
    }
    public int getLow(){
        return this.low;
    }    
    public int getAve(){
        return this.ave;
    }
}