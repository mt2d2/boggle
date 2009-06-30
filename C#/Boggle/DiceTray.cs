using System;
using System.Collections.Generic;
using System.Text;

class DiceTray
{
    private static Random random = new Random();
    public Die[,] dice { get; private set; }
    private int compareLength { get; set; } 

    public DiceTray()
    {
        List<string> godsDice = new List<string>();
        godsDice.Add("LRYTTE");
        godsDice.Add("ANAEEG");
        godsDice.Add("AFPKFS");
        godsDice.Add("YLDEVR");
        godsDice.Add("VTHRWE");
        godsDice.Add("IDSYTT");
        godsDice.Add("XLDERI");
        godsDice.Add("ZNRNHL");
        godsDice.Add("EGHWNE");
        godsDice.Add("OATTOW");
        godsDice.Add("HCPOAS");
        godsDice.Add("NMIQHU");
        godsDice.Add("SEOTIS");
        godsDice.Add("MTOICU");
        godsDice.Add("ENSIEU");
        godsDice.Add("OBBAOJ");

        Shuffle<string>(godsDice);

        // Assign game pieces, and delete temporary dice
        this.dice = new Die[4,4];
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                this.dice[row,col] = new Die(godsDice[0][random.Next(6)]);
                godsDice.RemoveAt(0);
            }
        }
    }

    public bool stringFound(string search)
    {
        search = search.ToUpper();
        this.compareLength = 0;
        char firstLetterOfSearch = search[0];

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (firstLetterOfSearch == this.dice[i,j].letter)
                    if (this.stringFound(search, i, j))
                        return true;
            }
        }

        return false;
    }

    private bool stringFound(string search, int row, int col)
    {
        if (row < 0 || row > 3 || col < 0 || col > 3)
            return false;

        Die die = this.dice[row,col];

        if (die.marked)
            return false;
        else if (search[this.compareLength] != die.letter)
            return false;
        else if ((search.Length - 1) == this.compareLength)
            return true;
        else
        {
            die.marked = true;
            this.compareLength++;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (!(i == 0 && j == 0))
                    {
                       if (this.stringFound(search, row + i, col + j))
                       {
                           die.marked = false;
                           return true;
                       }
                    }
                }
            }
        }

        die.marked = false;
        this.compareLength--;

        return false;
    }

    public string ToPattern()
    {
        StringBuilder sb = new StringBuilder();

        for (int row = 0; row < 4; row++)
            for (int col = 0; col < 4; col++)
                sb.Append(this.dice[row, col]);

        return sb.ToString();
    }

    public override String ToString()
    {
        StringBuilder sb = new StringBuilder();

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                sb.Append(this.dice[row,col].ToString());
            }

            sb.AppendLine();
        }

        return sb.ToString();
    }

    public static IList<T> Shuffle<T>(IList<T> deck)
    {
        int N = deck.Count;
        for (int i = 0; i < N; ++i)
        {
            int r = i + (int)(random.Next(N - i));
            T t = deck[r];
            deck[r] = deck[i];
            deck[i] = t;
        }

        return deck;
    }
}
