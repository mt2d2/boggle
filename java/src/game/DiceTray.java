package game;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class DiceTray
{
	private Die[][] dice;
	private int compareLength;
	
	public DiceTray()
	{
		Random random = new Random();
		
        ArrayList<String> godsDice = new ArrayList<String>();
        godsDice.ensureCapacity(16);
        godsDice.add("LRYTTE");
        godsDice.add("ANAEEG");
        godsDice.add("AFPKFS");
        godsDice.add("YLDEVR");
        godsDice.add("VTHRWE");
        godsDice.add("IDSYTT");
        godsDice.add("XLDERI");
        godsDice.add("ZNRNHL");
        godsDice.add("EGHWNE");
        godsDice.add("OATTOW");
        godsDice.add("HCPOAS");
        godsDice.add("NMIQHU");
        godsDice.add("SEOTIS");
        godsDice.add("MTOICU");
        godsDice.add("ENSIEU");
        godsDice.add("OBBAOJ");
        
        Collections.shuffle(godsDice);
        
        this.dice = new Die[4][4];
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                this.dice[row][col] = new Die(godsDice.get(0).charAt(random.nextInt(6)));
                godsDice.remove(0);
            }
        }
	}
	
	public Die[][] getDice()
	{
		return this.dice;
	}
	
    public boolean stringFound(String search)
    {
        search = search.toUpperCase();
        this.compareLength = 0;
        char firstLetterOfSearch = search.charAt(0);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (firstLetterOfSearch == this.dice[i][j].getLetter())
                    if (this.stringFound(search, i, j))
                        return true;
            }
        }

        return false;
    }

    private boolean stringFound(String search, int row, int col)
    {
        if (row < 0 || row > 3 || col < 0 || col > 3)
            return false;

        Die die = this.dice[row][col];

        if (die.isMarked())
            return false;
        else if (search.charAt(this.compareLength) != die.getLetter())
            return false;
        else if ((search.length() - 1) == this.compareLength)
            return true;
        else
        {
            die.setMarked(true);
            this.compareLength++;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (!(i == 0 && j == 0))
                    {
                       if (this.stringFound(search, row + i, col + j))
                       {
                           die.setMarked(false);
                           return true;
                       }
                    }
                }
            }
        }

        die.setMarked(false);
        this.compareLength--;

        return false;
    }

    public String toPattern()
    {
        StringBuilder sb = new StringBuilder();

        for (int row = 0; row < 4; row++)
            for (int col = 0; col < 4; col++)
                sb.append(this.dice[row][col]);

        return sb.toString().toLowerCase();
    }

    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                sb.append(this.dice[row][col].toString());
            }

            sb.append('\n');
        }

        return sb.toString();
    }
}
