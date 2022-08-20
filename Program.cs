namespace CarGame
{
    internal class Program
    {
        static void Main(string[] args)
        {
            BaseCar[] cars = {new Truck("Truck 1"),
                new SportCar("Sport Car 1"),
                new PassengerCar("Passenger Car 1"),
                new Bus("Bus 1"),
                new SportCar("Sport Car 2")};

            Race race = new Race(cars);
            race.Run();
        }
    }
}