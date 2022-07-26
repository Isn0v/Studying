using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tamagochi_Project
{
    internal class SingleTon
    {
        static private object toSend;

        static public void SendObject(object _toSend) { toSend = _toSend; }
        static public object ReceiveObject() { return toSend; }
    }

    public enum LifeLVLStatus
    {
        LVL_1 = 1,
        LVL_2 = 2,
        LVL_3 = 3,
        LVL_4 = 4,
        LVL_5 = 5,
    }
}
