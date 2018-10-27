/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxmlcalc;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

/**
 *
 * @author r231029r
 */
public class FXMLDocumentController implements Initializable {
   
    BigInteger reg = new BigInteger("0");   //表示するための変数
    BigDecimal register = new BigDecimal(0);    //新しく入ってきた値を格納する変数
    BigDecimal accum = new BigDecimal(0);       //今までの計算結果
    private boolean pointflag = false;
    enum Operater{ none, add, sub, mul, div, equal};
    Operater ope = Operater.none;
    
    @FXML
    private TextField accumulater;
    
    
    @FXML
    //数字を扱うメソッド
    private void keyAction(ActionEvent event){
        Button b = (Button)event.getSource();   //どのボタンが押されたか
        BigInteger val = new BigInteger(b.getText());   //ボタンに入っている数字を取得
        
        if (pointflag == false){
            reg = reg.multiply(new BigInteger("10"));       //regを１０倍
            reg = reg.add(val);         //regにvalの値を足し込む
            register = new BigDecimal(reg.toString());
            accumulater.setText(register.toPlainString());
        }
        else {
            reg = reg.multiply(new BigInteger("10"));       //regを１０倍
            reg = reg.add(val);         //regにvalの値を足し込む
            register = new BigDecimal(reg.toString()).divide(new BigDecimal("10")); //小数なのでregを1/10倍して、元に戻す
            accumulater.setText(register.toPlainString());
        }
    }
    
    @FXML
    //小数点が押されたかどうか
    private void point(){
        if(pointflag == false){ //まだ一回も「.」が入力されていなければ
            pointflag = true;   //flagを立てる
            accumulater.setText(register.toPlainString()+".");
        }
    }
    
    //各変数の値をクリアするメソッド
    private void clear(){
        pointflag = false;
        reg = new BigInteger("0");
        register = new BigDecimal("0");
        //accum = new BigDecimal("0");      //計算結果を残すためaccumは残しておく
    }
    
    //四則演算を計算するメソッド
    private void calc(){
        switch (ope){
            case none:          //なにも押されなかったら表示しない
                accum = register;
                return;
            case add:
                accum = accum.add(register);
                break;
            case sub:
                accum = accum.subtract(register);
                break;
            case mul:
                accum = accum.multiply(register);
                break;
            case div:
                accum = accum.divide(register,5,BigDecimal.ROUND_HALF_UP);      //小数第5位までに丸める
                break;
            case equal:
                accum = register;
                break;
        }
        accumulater.setText(accum.toPlainString()); //toPlainString()によって10.00000を10とかに表示する
    }
    
    @FXML
    private void addAction(ActionEvent event){
        calc();
        clear();
        ope = Operater.add;
    }
    
    @FXML
    private void subAction(ActionEvent event){
        calc();
        clear();
        ope = Operater.sub;
    }
    
    @FXML
    private void mulAction(ActionEvent event){
        calc();
        clear();
        ope = Operater.mul;
    }
    
    @FXML
    private void divAction(ActionEvent event){
        calc();
        clear();
        ope = Operater.div;
    }

    @FXML
    private void eqAction(ActionEvent event){
        calc();
        clear();
        ope = Operater.equal;
        /*
        int data = 0;
        data = register + Integer.parseInt(accumulater.getText());
        accumulater.setText(""+data);
        register = 0;
*/
    }

    @FXML
    //各変数をクリアし、registerの値を０にする
    private void clearAction(ActionEvent event){
        clear();    //変数をクリアするメソッド
        accum = new BigDecimal("0");
        accumulater.setText("0");
    }
    
    
    
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    
    
}
