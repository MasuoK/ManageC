import java.util.Comparator;

//比較用のクラス
public class TemperatureComparator implements Comparator<TemperatureInfo>{
    @Override
    public int compare(TemperatureInfo t1, TemperatureInfo t2){
        return t1.getHigh() < t2.getHigh() ? -1 : 1;
    }
    //文字列の比較はどうするか？
}