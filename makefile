project.o : newchess.h main.o coins.txt list.o newinitd.o getuserinput.o converfunc.o castling.o newgetprevloc.o newpawnsearch.o barrierfile.o simplebarrierfile.o newmove.o changestate.o printstate.o convprint.o match.o verifycheck.o checkmate.o declarewinner.o declaredraw.o checkfrompawns.o newcheckfromall.o undo.o newchessstack.o pawnpromotion.o resign.o writetofile.o readfromfile.o p_vs_p_mode.o comp_vs_p_mode.o savefile.o openmoves.o display_help.o offerdraw.o npassant.o undonpass.o draw.o piecemove.o enable.o generatemoves.o moveslist.o tree.o eval.o 
	cc main.o newinitd.o list.o getuserinput.o converfunc.o castling.o newgetprevloc.o newpawnsearch.o barrierfile.o simplebarrierfile.o newmove.o changestate.o printstate.o convprint.o match.o verifycheck.o checkmate.o declarewinner.o declaredraw.o checkfrompawns.o newcheckfromall.o undo.o newchessstack.o pawnpromotion.o resign.o writetofile.o readfromfile.o p_vs_p_mode.o comp_vs_p_mode.o  -lncursesw savefile.o openmoves.o display_help.o offerdraw.o npassant.o undonpass.o draw.o piecemove.o enable.o generatemoves.o moveslist.o tree.o eval.o -o project.o 
main.o : main.c newchess.h
	cc -c main.c -o main.o
p_vs_p_mode.o : p_vs_p_mode.c newchess.h
	cc -c p_vs_p_mode.c -o p_vs_p_mode.o
display_help.o : display_help.c newchess.h
	cc -c display_help.c -o display_help.o
comp_vs_p_mode.o : comp_vs_p_mode.c newchess.h
	cc -c comp_vs_p_mode.c -o comp_vs_p_mode.o
newinitd.o : newinitd.c newchess.h
	cc -c newinitd.c -o newinitd.o
list.o : list.c newchess.h
	cc -c list.c -o list.o
getuserinput.o : getuserinput.c newchess.h
	cc -c getuserinput.c newchess.h
converfunc.o : converfunc.c newchess.h
	cc -c converfunc.c -o converfunc.o
castling.o : castling.c newchess.h
	cc -c castling.c -o castling.o
newgetprevloc.o : newgetprevloc.c newchess.h
	cc -c newgetprevloc.c -o newgetprevloc.o
newpawnsearch.o : newpawnsearch.c newchess.h
	cc -c newpawnsearch.c -o newpawnsearch.o
barrierfile.o : barrierfile.c newchess.h
	cc -c barrierfile.c -o barrierfile.o
simplebarrierfile.o : simplebarrierfile.c newchess.h
	cc -c simplebarrierfile.c -o simplebarrierfile.o
newmove.o : newmove.c newchess.h
	cc -c newmove.c -o newmove.o
changestate.o : changestate.c newchess.h
	cc -c changestate.c -o changestate.o
printstate.o : printstate.c newchess.h
	cc -c printstate.c -o printstate.o
convprint.o : convprint.c newchess.h
	cc -c convprint.c -o convprint.o
match.o : match.c newchess.h
	cc -c match.c -o match.o
verifycheck.o : verifycheck.c newchess.h
	cc -c verifycheck.c -o verifycheck.o
checkmate.o : checkmate.c newchess.h
	cc -c checkmate.c -o checkmate.o
declarewinner.o : declarewinner.c newchess.h
	cc -c declarewinner.c -o declarewinner.o
checkfrompawns.o : checkfrompawns.c newchess.h
	cc -c checkfrompawns.c -o checkfrompawns.o
newcheckfromall.o : newcheckfromall.c newchess.h
	cc -c newcheckfromall.c -o newcheckfromall.o
undo.o : undo.c newchess.h
	cc -c undo.c -o undo.o
newchessstack.o : newchessstack.c newchess.h
	cc -c newchessstack.c -o newchessstack.o
pawnpromotion.o : pawnpromotion.c newchess.h
	cc -c pawnpromotion.c -o pawnpromotion.o
resign.o : resign.c newchess.h
	cc -c resign.c -o resign.o
writetofile.o : writetofile.c newchess.h
	cc -c writetofile.c -o writetofile.o
readfromfile.o : readfromfile.c newchess.h
	cc -c readfromfile.c -o readfromfile.o
savefile.o : savefile.c newchess.h
	cc -c savefile.c -o savefile.o
openmoves.o : openmoves.c newchess.h
	cc -c openmoves.c -o openmoves.o
declaredraw.o : declaredraw.c newchess.h
	cc -c declaredraw.c -o declaredraw.o
offerdraw.o : offerdraw.c newchess.h
	cc -c offerdraw.c -o offerdraw.o
npassant.o : npassant.c newchess.h
	cc -c npassant.c -o npassant.o
undonpass.o : undonpass.c newchess.h
	cc -c undonpass.c -o undonpass.o
draw.o : draw.c newchess.h
	cc -c draw.c -o draw.o
piecemove.o : piecemove.c newchess.h
	cc -c piecemove.c -o piecemove.o
enable.o : enable.c newchess.h
	cc -c enable.c -o enable.o
generatemoves.o : generatemoves.c newchess.h
	cc -c generatemoves.c -o generatemoves.o
moveslist.o : moveslist.c newchess.h
	cc -c moveslist.c -o moveslist.o
tree.o : tree.c newchess.h
	cc -c tree.c -o tree.o
eval.o : eval.c newchess.h
	cc -c eval.c -o eval.o


clean :
	rm *.o
	rm *~
