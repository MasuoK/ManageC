/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxmlcalc;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

/**
 *
 * @author r231029r
 */
public class JavaFXMLCalc extends Application {
    
    private int register = 0;
    private boolean opeAdd = false;
    
    @FXML
    private TextField accumulater;
    
    
    @FXML
    private void keyAction(ActionEvent event){
        Button b = (Button)event.getSource();
        if(opeAdd == true){
            accumulater.setText("0");
            opeAdd = false;
        }
        int data = Integer.parseInt(accumulater.getText());
        data = data * 10 + Integer.parseInt(b.getText());
        accumulater.setText(""+data);
    }
    
    @FXML
    private void addAction(ActionEvent event){
        int data = register + Integer.parseInt(accumulater.getText());
        accumulater.setText(""+data);
        register = data;
        opeAdd = true;
    }
    
    @FXML
    private void subAction(ActionEvent event){
        int data = register - Integer.parseInt(accumulater.getText());
        accumulater.setText(""+data);
        register = data;
        opeAdd = false;
    }
    
    
    @FXML
    private void eqAction(ActionEvent event){
        int data = register + Integer.parseInt(accumulater.getText());
        accumulater.setText(""+data);
        register = 0;
        opeAdd = false; 
    }

    @FXML
    private void clearAction(ActionEvent event){
        register = 0;
        accumulater.setText("0");
        opeAdd = false;
    }
    
    @Override
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("FXMLDocument.fxml"));
        
        Scene scene = new Scene(root);
        
        stage.setScene(scene);
        stage.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
