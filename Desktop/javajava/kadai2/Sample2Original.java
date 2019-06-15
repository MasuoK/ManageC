import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
 
class Sample2Original{
  public static void main(String args[]) {
    try {
      File f = new File("sample.csv");
      BufferedReader br = new BufferedReader(new FileReader(f));
 
      String[][] data = new String[2][2];
      String line = br.readLine();
      for (int row = 0; line != null; row++) {
        data[row] = line.split(",", 0);
        line = br.readLine();
      }
      br.close();
 
      // CSVから読み込んだ配列の中身を表示
      for(int row = 0; row < data.length; row++) {
        for(int col = 0; col < data.length; col++) {
          System.out.println(data[row][col]);
        }
      } 
 
    } catch (IOException e) {
      System.out.println(e);
    }
  }
}