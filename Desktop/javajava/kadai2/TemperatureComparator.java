import java.util.Comparator;

//比較用のクラス
public class TemperatureComparator implements Comparator<TemperatureInfo>{
    //compareの比較:high,low,ave,dayの優先順に比較
    //high,low,aveは降順,日付は昇順にする
    @Override
    public int compare(TemperatureInfo t1, TemperatureInfo t2){
        if(t1.getHigh() < t2.getHigh()){
            return 1;
        } else if(t1.getHigh() > t2.getHigh()){
            return -1;
        } else{
            if(t1.getLow() < t2.getLow()){
                return 1;
            } else if(t1.getLow() > t2.getLow()){
                return -1;
            } else{
                if(t1.getAve() < t2.getAve()){
                    return 1;
                } else if(t1.getAve() > t2.getAve()){
                    return -1;
                } else{
                    //compareTo: t1よりt2が辞書的に後ろなら-1, 前なら1, 同じなら0を返す
                    return t1.getDay().compareTo(t2.getDay());
                }
            }
        }
    }
    //文字列の比較はどうするか？
}