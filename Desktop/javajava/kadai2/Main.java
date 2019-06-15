//エンジニアの入り口 Java演習問題 オブジェクト指向編より

import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList; //ArrayListを使うのに必要

public class Main{
    public static void main(String args[]) {
        try {
          File f = new File("data.csv");
          BufferedReader br = new BufferedReader(new FileReader(f));
     
          String line;
          ArrayList<String> datalist = new ArrayList<String>();

          // 1行ずつCSVファイルを読み込む
          while ((line = br.readLine()) != null) {
              //ここでdataを宣言するということは、dataが有効なのはwhileの中のみ
            String[] data = line.split(",", 0); // 行をカンマ区切りで配列に変換
     
            //String elem
            //配列dataから１つ要素取り出し、elemに代入
            //それを全ての要素を取り出すまでループを繰り返す
            for (String elem : data) {
                datalist.add(elem);
                //datalist.sizeでリストの長さを取れる
                //System.out.println(elem);
            }
          }
          //フィールドArrayList <String> .sizeは表示されません。
          //正しくはArrayList.size()
          //datamat:datalistは全データが入るので、4で割った数が行になる
          //列は日付、最高気温、最低気温、平均気温の4つ
          String[][] datamat = new String[datalist.size()/4][4];
          //row:行,col:列
          for(int row = 0; row < datalist.size()/4 ; row++) {
            for(int col = 0; col < 4; col++) {
                //リストの要素を取り出して２次配列に格納
                datamat[row][col] = datalist.get(row * 4 + col);
                System.out.print(datamat[row][col]+" ");
            }
            System.out.println();
          }
          br.close();
     
        } catch (IOException e) {
          System.out.println(e);
        }
      }
}