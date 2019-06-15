public class Mycar extends AbstractAutomobile{

    protected Mycar(){
        this.setCarType(CarType.STANDERD_CAR);
    }

    @Override
    public int getCapacity(){
        return 7;
    }

    @Override
    public String getCarModel(){
        return "自家用ワンボックス車";
    }
}