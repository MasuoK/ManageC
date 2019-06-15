//data.csvを読み込んで配列に格納し、出力するプログラム
//このプログラムがやってること(whileの中)
//1. コンマ区切りで一行読み込み、dataに代入する(コンマで区切られたデータは何らかの手段で別々に分けている)
//2. そのデータ(つまり一行)を要素ごとに出力する
//3. 1,2をcsvファイルの中全部に対して繰り返す
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
 
class Sample {
  public static void main(String args[]) {
    try {
      File f = new File("data.csv");
      BufferedReader br = new BufferedReader(new FileReader(f));
 
      String line;
      // 1行ずつCSVファイルを読み込む
      while ((line = br.readLine()) != null) {
        String[] data = line.split(",", 0); // 行をカンマ区切りで配列に変換
 
        for (String elem : data) {
          System.out.println(elem);
        }
      }
      br.close();
 
    } catch (IOException e) {
      System.out.println(e);
    }
  }
}