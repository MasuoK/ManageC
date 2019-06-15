//エンジニアの入り口 Java演習問題 オブジェクト指向編より

public class Main{
    public static void main(String[] args){
        Mycar car = new Mycar();
        System.out.println("車種(モデル)は" + car.getCarModel() + "です");
        System.out.println("乗車定員は" + car.getCapacity() + "人です");
        System.out.println("車種区分は" + car.getCarTypeString() + "です");
    }
}