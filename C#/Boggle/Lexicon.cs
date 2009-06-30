using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

class Lexicon
{
    private string file { get; set; }
    private List<string> dictionary;
    private List<string> lexicon;

    public Lexicon(string file)
    {
        this.file = file;
        this.dictionary = new List<string>();
        this.lexicon = new List<string>();

        this.load();
    }

    private void load()
    {
        using (StreamReader reader = new StreamReader(this.file))
        {
            string line;
            while ((line = reader.ReadLine()) != null)
            {
                this.dictionary.Add(line);
            }
        }
    }

    public void filterLexicon(string pattern)
    {
        // clear the lexicon first
        this.lexicon.Clear();

        // build a regexp that will only allow certain characters
        Regex rx = new Regex("[" + pattern + "]+", RegexOptions.Compiled | RegexOptions.IgnoreCase);

        foreach (string s in this.dictionary)
            if (rx.IsMatch(s))
                this.lexicon.Add(s);
    }

    public bool hasWord(string word)
    {
        return (this.lexicon.BinarySearch(word) >= 0);
    }

    public IEnumerator<string> GetEnumerator()
    {
        return this.lexicon.GetEnumerator();
    }
}