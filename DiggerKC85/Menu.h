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

const MultiLang lang_resume[]= {
               { LANG_EN, "      resume" },
               { LANG_DE, "      zur\175ck" },
               { LANG_FR, "        dos" },
};
const MultiLang lang_new[]= {
               { LANG_EN, "     New Game" },
               { LANG_DE, "    Neues Spiel" },
               { LANG_FR, "  Nouvelle partie" },
};
const MultiLang lang_levelup[]= {
               { LANG_EN, "     Level up" },
               { LANG_DE, "     Level vor" },
               { LANG_FR, "   Niveau suivant" },
};
const MultiLang lang_leveldown[]= {
               { LANG_EN, "    Level down" },
               { LANG_DE, "    Level zur\175ck" },
               { LANG_FR, "  Niveau pr\133c\133dent" },
};
const MultiLang lang_toggle_easy[]= {
               { LANG_EN, "    Mode (easy)" },
               { LANG_DE, "   Modus (leicht)" },
               { LANG_FR, "   Mode (facile)" },
};
const MultiLang lang_toggle_hard[]= {
               { LANG_EN, "    Mode (hard)" },
               { LANG_DE, "   Modus (schwer)" },
               { LANG_FR, "  Mode (difficile)" },
};

const MultiLang lang_title[]= {
               { LANG_EN, "    D I G G E R"},
               { LANG_DE, "    D I G G E R"},
               { LANG_FR, "    D I G G E R"},
};

const MultiLang lang_score_easy[]= {
               { LANG_EN, "     (easy)"},
               { LANG_DE, "   (leicht)"},
               { LANG_FR, "   (facile)"},
};

const MultiLang lang_score_hard[]= {
               { LANG_EN, "     (hard)"},
               { LANG_DE, "   (schwer)"},
               { LANG_FR, "(difficile)"},
};
