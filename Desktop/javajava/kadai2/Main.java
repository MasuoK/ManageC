import java.util.Collections;

//エンジニアの入り口 Java演習問題 オブジェクト指向編より

import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList; //ArrayListを使うのに必要
import java.util.Collections;

public class Main{
    public static void main(String args[]) {
        try {
          File f = new File("data.csv");
          BufferedReader br = new BufferedReader(new FileReader(f));
     
          String line;
          ArrayList<TemperatureInfo> datalist = new ArrayList<TemperatureInfo>();

          // 1行ずつCSVファイルを読み込む
          while ((line = br.readLine()) != null) {
              //ここでdataを宣言するということは、dataが有効なのはwhileの中のみ
            String[] data = line.split(",", 0); // 行をカンマ区切りで配列に変換
     
            datalist.add(new TemperatureInfo(data[0],Float.valueOf(data[1]),Float.valueOf(data[2]),Float.valueOf(data[3])));
          }
          //row:行,col:列
          /*
          for(int row = 0; row < datalist.size()/4 ; row++) {
            for(int col = 0; col < 4; col++) {
                System.out.println(datalist.get(row * 4 + col) + " ");
            }
            System.out.println();
          }*/

          Collections.sort(datalist,new TemperatureComparator());

          for(TemperatureInfo t: datalist){
            System.out.println(t.getHigh() + " " + t.getLow() + " " + t.getAve() + " "  + t.getDay());
          }
          br.close();
     
        } catch (IOException e) {
          System.out.println(e);
        }
      }
}