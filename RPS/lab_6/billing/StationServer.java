import Cell.*;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;

import java.util.Properties;
import java.util.Map;
import java.util.HashMap;

// Класс, реализующий IDL-интерфейс базовой станции
class StationServant extends StationPOA {
  /*
   * TubeCallback tubeRef;
   * String tubeNum;
   */
  Map<String, TubeCallback> tubesInCell = new HashMap<String, TubeCallback>();
  Map<String, String> tubeBalance = new HashMap<String, String>();

  // Стоимость отправки сообщения
  Integer priceOfMessage = 10;

  // Метод регистрации трубки в базовой станции
  public int register(TubeCallback objRef, String phoneNum, String balance) {
    /*
     * tubeRef = objRef;
     * tubeNum = phoneNum;
     * balance = баланс телефона
     */
    tubesInCell.put(phoneNum, objRef);
    tubeBalance.put(phoneNum, balance);
    System.out.println("Станция: зарегистрирована трубка " + phoneNum);
    System.out.println("Станция: всего зарегистрировано: " + tubesInCell.size());
    System.out.println("Баланс трубки: " + balance);
    return (1);
  };

  // Метод пересылки сообщения от трубки к трубке
  public int getSMS(String fromNum, String toNum, String message) {
    System.out.println("Станция: трубка " + fromNum + " посылает сообщение " + toNum);

    // Здесь должен быть поиск объектной ссылки по номеру toNum
    tubesInCell.get(toNum).getSMS(fromNum, message);

    // Получаем баланс отправителя после отправки сообщения
    Integer sender_balance = Integer.parseInt(tubeBalance.get(fromNum));

    // Уменьшение баланса отправителя
    String new_balance = "" + (sender_balance - priceOfMessage);
    tubeBalance.put(fromNum, new_balance);

    return (1);
  };

  // Метод пересылки сообщения от трубки к трубке
  public int getBalance(String tubeNumber) {
    String balance = tubeBalance.get(tubeNumber);

    tubesInCell.get(tubeNumber).getBalance(tubeNumber, balance);

    return (1);
  };
};

// Класс, реализующий сервер базовой станции
public class StationServer {

  public static void main(String args[]) {
    try {
      // Создание и инициализация ORB
      ORB orb = ORB.init(args, null);

      // Получение ссылки и активирование POAManager
      POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
      rootpoa.the_POAManager().activate();

      // Создание серванта для CORBA-объекта "базовая станция"
      StationServant servant = new StationServant();

      // Получение объектной ссылки на сервант
      org.omg.CORBA.Object ref = rootpoa.servant_to_reference(servant);
      Station sref = StationHelper.narrow(ref);

      org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
      NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);

      // Связывание объектной ссылки с именем
      String name = "BaseStation";
      NameComponent path[] = ncRef.to_name(name);
      ncRef.rebind(path, sref);

      System.out.println("Сервер готов и ждет ...");

      // Ожидание обращений от клиентов (трубок)
      orb.run();
    } catch (Exception e) {
      System.err.println("Ошибка: " + e);
      e.printStackTrace(System.out);
    }
    ;
  };

};
