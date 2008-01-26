icl vecliball.h /EP > _temp_pp.h
uncrustify -c c:\path\uncrustify\klaus.cfg _temp_pp.h
del vecliball_pp.h
ren _temp_pp.h.uncrustify vecliball_pp.h
del _temp_pp.h