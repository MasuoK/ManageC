//二次配列に変換するサンプル(mainの例外が発生して実行できない)
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
 
class Sample2 {
  public static void main(String args[]) {
    try {
      File f = new File("data.csv");
      BufferedReader br = new BufferedReader(new FileReader(f));

      String[] data = line.split(",", 0);
      ArrayList<String> datalist = new ArrayList<String>();

      String line = br.readLine();
      for (int row = 0; line != null; row++) {
        datalist.add(data[row]);
        line = br.readLine();
      }
      br.close();
 
      // CSVから読み込んだ配列の中身を表示
      for(int row = 0; row < datalist.length; row++) {
        for(int col = 0; col < datalist.length; col++) {
          System.out.println(datalist);
        }
      } 
 
    } catch (IOException e) {
      System.out.println(e);
    }
  }
}