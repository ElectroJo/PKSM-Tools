using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using PKHeX.Core;
using System.Text;

namespace serveLegality
{
    class Program
    {
        private const int PKSIZE = 232;
        private const String HEADER = "PKSMOTA";
        private const int GAME_LEN = 1;
        private const int GEN6 = 6;
        private const int GEN7 = 7;
        private const string MGDatabasePath = "mgdb";

        static void Main(string[] args)
        {
            byte[] bytes = System.IO.File.ReadAllBytes(args[0]);

            bool verbose = true;

            Console.WriteLine("Loading mgdb in memory...");
            Legal.RefreshMGDB(MGDatabasePath);

            byte[] inputBuffer = new byte[HEADER.Length + GAME_LEN + PKSIZE];
            byte[] outputBuffer = new byte[HEADER.Length + GAME_LEN + PKSIZE];

            while (true)
            {
                try
                {
                    PrintLegality(bytes, verbose);
                    PKM pk = GetPKMFromPayload(bytes);
                    ServeLegality.AutoLegality al = new ServeLegality.AutoLegality();
                    PKM legal = al.LoadShowdownSetModded_PKSM(pk);

                    Array.Copy(Encoding.ASCII.GetBytes(HEADER), 0, outputBuffer, 0, HEADER.Length);
                    Array.Copy(legal.Data, 0, outputBuffer, 7, PKSIZE);
                    File.WriteAllBytes(args[1], outputBuffer);
                    break;
                }
                catch (Exception e)
                {
                    Console.WriteLine("Error" + e.StackTrace);
                }
            }
        }
        public static PKM GetPKMFromPayload(byte[] inputBuffer)
        {
            byte[] pkmData = new byte[PKSIZE];
            Array.Copy(inputBuffer, HEADER.Length + GAME_LEN, pkmData, 0, 232);
            PKM pk;

            byte version = inputBuffer[HEADER.Length];
            switch (version)
            {
                case GEN6:
                    pk = new PK6(pkmData);
                    break;
                case GEN7:
                    pk = new PK7(pkmData);
                    break;
                default:
                    pk = new PK7();
                    break;
            }

            return pk;
        }

        public static void PrintLegality(byte[] inputBuffer, bool verbose)
        {
            GameInfo.GameStrings gs = GameInfo.GetStrings("en");
            PKM pk = GetPKMFromPayload(inputBuffer);
            LegalityAnalysis la = new LegalityAnalysis(pk);
            Console.WriteLine("===================================================================");
            Console.WriteLine("Received: " + gs.specieslist[pk.Species] + "\n" + la.Report(verbose));
            Console.WriteLine("===================================================================");
        }
    }
}
