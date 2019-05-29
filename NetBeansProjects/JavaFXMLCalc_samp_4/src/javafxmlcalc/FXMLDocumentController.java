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
    enum Function{none,sin,cos,tan,log,root};
    Function fun = Function.none;               //funの状態
    Operater ope = Operater.none;               //opeの状態
    private boolean keyflag = false;            //数字が入力されたかどうかのフラグ
    private boolean consflag = false;           //定数(eまたはπ）が押されたかどうかのフラグ 
    
    @FXML
    private TextField accumulater;
    
    
    @FXML
    //数字を扱うメソッド
    private void keyAction(ActionEvent event){
        keyflag = true;
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
    private void eAction(ActionEvent event){
        if(consflag == true){    //定数が２連続以上で押された場合初期化する
            clear();
            accum = new BigDecimal("0");
            accumulater.setText(accum.toPlainString()); 
            ope = Operater.none;
            fun = Function.none;
            return;
        }
        consflag = true;
        register = new BigDecimal(Math.E);
        accumulater.setText(register.toPlainString());
    }
    
    @FXML
    private void piAction(ActionEvent event){
        if(consflag == true){    //定数が２連続以上で押された場合初期化する
            clear();
            accum = new BigDecimal("0");
            accumulater.setText(accum.toPlainString()); 
            ope = Operater.none;
            fun = Function.none;
            return;
        }
        consflag = true;
        register = new BigDecimal(Math.PI);
        accumulater.setText(register.toPlainString());
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
        keyflag = false;
        consflag = false;
        pointflag = false;
        reg = new BigInteger("0");
        register = new BigDecimal("0");
        //accum = new BigDecimal("0");      //計算結果を残すためaccumは残しておく
    }
    
    //四則演算を計算するメソッド
    private void calc(){
        if(keyflag == false && consflag == false){       //演算子が2連続以上入力された場合(keyflagもconsflagも立っていない場合)全て初期化する。
            clear();
            accum = new BigDecimal("0");
            accumulater.setText(accum.toPlainString()); 
            ope = Operater.none;
            fun = Function.none;
            return;
        }
        
        switch (ope){
            case none:      //なにも押されなかったら表示しない
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
    
    private void func(){
        switch(fun){
            case none:
                return;
            case sin:
                register = new BigDecimal(Math.sin(Math.toRadians(register.doubleValue())));
                fun = Function.none;
                break;
            case cos:
                register = new BigDecimal(Math.cos(Math.toRadians(register.doubleValue())));
                fun = Function.none;
                break;
            case tan:
                register = new BigDecimal(Math.tan(Math.toRadians(register.doubleValue())));
                fun = Function.none;
                break;
            case log:
                register = new BigDecimal(Math.log(register.doubleValue()));
                fun = Function.none;
                break;
            case root:
                register = new BigDecimal(Math.sqrt(register.doubleValue()));
                fun = Function.none;
                break;
        }
        accumulater.setText(register.toPlainString());
}
    @FXML
    private void sinAction(ActionEvent event){
        func();
        clear();
        accumulater.setText("sin");
        fun = Function.sin;
    }
    
    @FXML
    private void cosAction(ActionEvent event){
        func();
        clear();
        accumulater.setText("cos");
        fun = Function.cos;
    }
    
    @FXML
    private void tanAction(ActionEvent event){
        func();
        clear();
        accumulater.setText("tan");
        fun = Function.tan;
    }
    
    @FXML
    private void logAction(ActionEvent event){
        func();
        clear();
        accumulater.setText("log");
        fun = Function.log;
    }
    
    @FXML
    private void rootAction(ActionEvent event){
        func();
        clear();
        accumulater.setText("√");
        fun = Function.root;
    }
    
    @FXML
    private void addAction(ActionEvent event){
        func();
        calc();
        clear();
        ope = Operater.add;     //opeを更新
    }
    
    @FXML
    private void subAction(ActionEvent event){
        func();
        calc();
        clear();
        ope = Operater.sub;     //opeを更新
    }
    
    @FXML
    private void mulAction(ActionEvent event){
        func();
        calc();
        clear();
        ope = Operater.mul;
    }
    
    @FXML
    private void divAction(ActionEvent event){
        func();
        calc();
        clear();
        ope = Operater.div;
    }

    @FXML
    private void eqAction(ActionEvent event){
        func();
        calc();
        clear();
        ope = Operater.equal;
    }

    @FXML
    //各変数をクリアし、registerの値を０にする
    private void clearAction(ActionEvent event){
        clear();    //変数をクリアするメソッド
        accum = new BigDecimal("0");
        accumulater.setText("0");
        ope = Operater.none;        //オペレータの状態も初期化
        fun = Function.none;
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    
    
}
