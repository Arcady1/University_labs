import Cell.*;
import org.omg.CosNaming.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;
import java.io.*;
import java.lang.Character;

import java.util.Random;

// Класс вызова телефонной трубки
class TubeCallbackServant extends TubeCallbackPOA {

  String myNum; // Номер трубки

  // Конструктор класса
  TubeCallbackServant(String num) {
    myNum = num;
  };

  // Метод обработки принятого сообщения
  public int getSMS(String fromNum, String message) {
    System.out.println(myNum + ": message is received from the " + fromNum + ": " + message);
    return (1);
  };

  // Метод получения баланса
  public int getBalance(String tubeNumber, String tubeBalance) {
    System.out.println("Tube balance with number: " + tubeNumber + ": " + tubeBalance);
    return (1);
  };

  // Метод, возвращающий номер трубки
  public String getNum() {
    return (myNum);
  };

};

// Класс, используемый для создания потока управления
class ORBThread extends Thread {

  ORB myOrb;

  // Конструктор класса
  ORBThread(ORB orb) {
    myOrb = orb;
  };

  // Метод запуска потока
  public void run() {
    myOrb.run();
  };

};

// Класс, имитирующий телефонную трубку
public class Tube {

  private static Random random = new Random();

  public static void main(String args[]) {
    try {
      Integer num = random.nextInt(10000);
      String myNum = num.toString(); // Номер трубки
      String balance = "50"; // Баланс телефона
      // Создание и инициализация ORB
      ORB orb = ORB.init(args, null);

      // Создание серванта для IDL-интерфейса TubeCallback
      POA rootPOA = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
      rootPOA.the_POAManager().activate();
      TubeCallbackServant listener = new TubeCallbackServant(myNum);
      rootPOA.activate_object(listener);
      // Получение ссылки на сервант
      TubeCallback ref = TubeCallbackHelper.narrow(rootPOA.servant_to_reference(listener));

      // Получение контекста именования
      org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
      NamingContext ncRef = NamingContextHelper.narrow(objRef);

      // Преобразование имени базовой станции в объектную ссылку
      NameComponent nc = new NameComponent("BaseStation", "");
      NameComponent path[] = { nc };
      Station stationRef = StationHelper.narrow(ncRef.resolve(path));

      // Регистрация трубки в базовой станции
      stationRef.register(ref, myNum, balance);
      System.out.println("The handset base station is registered under the number: " + myNum);

      // Запуск ORB в отдельном потоке управления
      // для прослушивания вызовов трубки
      ORBThread orbThr = new ORBThread(orb);
      orbThr.start();

      // Бесконечный цикл чтения строк с клавиатуры и отсылки их
      // базовой станции
      BufferedReader inpt = new BufferedReader(new InputStreamReader(System.in));
      String msg;
      String toNum;
      boolean s;
      int k;
      k = 0;

      while (true) {
        System.out.println("Enter the number of the recipient or '*100#' to get the balance: ");
        toNum = inpt.readLine();

        if (toNum.equals("*100#")) {
          stationRef.getBalance(myNum);
        } else {
          System.out.println("Enter your message: ");

          String message = inpt.readLine();

          stationRef.getSMS(myNum, toNum, message);
        }
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
    ;

  };

};
