using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CarGame
{
    internal class Race
    {
        private BaseCar[] cars;
        private event CarGameHandler? handler;

        public const int FullWay = 1000;

        public BaseCar[] Cars { get => cars; }

        public Race(params BaseCar[] cars)
        {
            this.cars = cars;
        }


        public void Run()
        {
            Console.WriteLine($"The full way of the race is {FullWay} km\n");
            Random r = new Random();
            handler += BaseCar.finishEvent;
            bool breakCycle = false;
            while (true)
            {
                foreach(BaseCar car in cars)
                {
                    car.Drive(r);
                    car.State();
                    if (car.isFinished(FullWay))
                    {
                        handler.Invoke(car);
                        breakCycle = true;
                        break;
                    }
                }
                Console.WriteLine();
                if (breakCycle)
                {
                    break;
                }
            }
        }


    }

    delegate void CarGameHandler(BaseCar car);
}
