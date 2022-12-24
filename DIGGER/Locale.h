/*
https://gamebuino.com/academy/standalone/create-a-multilingual-game
https://www.htmlhelp.com/reference/charset/latin1.gif  Code-32=Char, Dezimal --> Oktal

Sonderzeichen oktal:
\133 = e´
\175 = ü
*/

const MultiLang lang_score[]= {
               { LANG_EN, "     Highscore" },
               { LANG_DE, "     Highscore" },
               { LANG_FR, "    Score \133lev\133" },
};
const MultiLang lang_highscore[]= {
               { LANG_EN, "HIGHSCORE :" },
               { LANG_DE, "HIGHSCORE :" },
               { LANG_FR, "Score \133lev\133" },
};
const MultiLang lang_name[]= {
               { LANG_EN, "your name?" },
               { LANG_DE, "dein Name?" },
               { LANG_FR, "votre nom" },
};
