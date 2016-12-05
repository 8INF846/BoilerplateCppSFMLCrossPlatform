:- dynamic(light/2).
:- dynamic(poop/2).
:- dynamic(walkable/2).
:- dynamic(wind/2).
:- dynamic(visited/2).
:- dynamic(shooted/2).
:- dynamic(hole/2).

setVisited(X,Y) :- assert(visited(X,Y)).
setWalkable(X,Y) :- assert(walkable(X,Y)).
setPoop(X,Y) :- assert(poop(X,Y)).
setShooted(X,Y) :- assert(shooted(X,Y)).
setLight(X,Y) :- assert(light(X,Y)).
setHole(X,Y) :- assert(hole(X,Y)).
removeLight(X,Y) :- retractall(light(X,Y)).
removePoop(X,Y) :- retractall(poop(X,Y)).
removeWalkable(X,Y) :- retractall(walkable(X,Y)).
removeWind(X,Y) :- retractall(wind(X,Y)).
removeVisited(X,Y) :- retractall(visited(X,Y)).
removeShooted(X,Y) :- retractall(shooted(X,Y)).
removeHole(X,Y) :- retractall(hole(X,Y)).

/*If we find the portal*/
portal(X,Y) :- light(X,Y).
runOut(X,Y) :- portal(X,Y).

/*If we are on a Poop, we can shoot*/
safe(X,Y) :- visited(X,Y), not(poop(X,Y)), not(wind(X,Y)), not(hole(X,Y)).

shootNorth(X,Y) :-
N is Y-1,
poop(X,Y), walkable(X,N), not(shooted(X,N)), not(visited(X,N)).

shootSouth(X,Y) :-
S is Y+1,
poop(X,Y), walkable(X,S), not(shooted(X,S)), not(visited(X,S)).

shootWest(X,Y) :-
W is X-1,
poop(X,Y), walkable(W,Y), not(shooted(W,Y)), not(visited(W,Y)).

shootEast(X,Y) :-
E is X+1,
poop(X,Y), walkable(E,Y), not(shooted(E,Y)), not(visited(E,Y)).

/*If we have a barrier*/
/*Ex:
Pw.  PwH
wHw  w.w
.w.  Hw.
*/

detectBarrier(X,Y):-
S is Y+1, N is Y-1, E is X+1, W is X-1,
((safe(X,N), wind(X,Y), wind(E,N)) ;
(safe(X,S), wind(X,Y), wind(E,S)) ;
(safe(X,N), wind(X,Y), wind(W,N)) ;
(safe(X,S), wind(X,Y), wind(W,S)) ;
(safe(W,Y), wind(X,Y), wind(W,N)) ;
(safe(W,Y), wind(X,Y), wind(W,S)) ;
(safe(E,Y), wind(X,Y), wind(E,N)) ;
(safe(E,Y), wind(X,Y), wind(E,S))).

detectHoleNorth(X,Y):-
S is Y+1, N is Y-1, E is X+1, W is X-1,
SS is Y+2, NN is Y-2, EE is X+2, WW is X-2,
((wind(X,Y), wind(W,N), wind(X,NN)) ;
(wind(X,Y), wind(W,N), wind(E,N)) ;
(wind(X,Y), wind(E,N), wind(X,NN))).

detectHoleSouth(X,Y):-
S is Y+1, N is Y-1, E is X+1, W is X-1,
SS is Y+2, NN is Y-2, EE is X+2, WW is X-2,
((wind(X,Y), wind(W,S), wind(X,SS)) ;
(wind(X,Y), wind(W,S), wind(E,S)) ;
(wind(X,Y), wind(E,S), wind(X,SS))).

detectHoleWest(X,Y):-
S is Y+1, N is Y-1, E is X+1, W is X-1,
SS is Y+2, NN is Y-2, EE is X+2, WW is X-2,
((wind(X,Y), wind(E,N), wind(EE,Y)) ;
(wind(X,Y), wind(E,N), wind(E,S)) ;
(wind(X,Y), wind(E,S), wind(EE,Y))).

detectHoleEast(X,Y):-
S is Y+1, N is Y-1, E is X+1, W is X-1,
SS is Y+2, NN is Y-2, EE is X+2, WW is X-2,
((wind(X,Y), wind(W,N), wind(WW,Y)) ;
(wind(X,Y), wind(W,N), wind(W,S)) ;
(wind(X,Y), wind(W,S), wind(WW,Y))).

avoidBarrierBySouth(X,Y):-
S is Y+1, N is Y-1, E is X+1, W is X-1,
walkable(X,S), wind(X,Y), not(visited(X,S)).

avoidBarrierByNorth(X,Y):-
S is Y+1, N is Y-1, E is X+1, W is X-1,
walkable(X,N), wind(X,Y), not(visited(X,N)).

avoidBarrierByEast(X,Y):-
S is Y+1, N is Y-1, E is X+1, W is X-1,
walkable(E,Y), wind(X,Y), not(visited(E,Y)).

avoidBarrierByWest(X,Y):-
S is Y+1, N is Y-1, E is X+1, W is X-1,
walkable(W,Y), wind(X,Y), not(visited(W,Y)).

/*Choose next case*/
goNorth(X,Y) :-
N is Y-1, W is X-1, E is X+1, walkable(X, N),
(safe(X,Y) ;
(wind(X,Y),
(safe(X,N) ;
(not(visited(X,N)), (safe(E,N) ; safe(W,N))) ;
(detectBarrier(X,Y) , avoidBarrierByNorth(X,Y), not(detectHoleNorth(X,Y)))
))).

goSouth(X,Y) :-
S is Y+1, W is X-1, E is X+1, walkable(X, S),
(safe(X,Y) ;
(wind(X,Y),
(safe(X,S) ;
(not(visited(X,S)), (safe(E,S) ; safe(W,S))))) ;
(detectBarrier(X,Y) , avoidBarrierBySouth(X,Y), not(detectHoleSouth(X,Y)))
).

goWest(X,Y) :-
W is X-1, S is Y+1, N is Y-1, walkable(W, Y),
(safe(X,Y) ;
(wind(X,Y),
(safe(W,Y) ;
(not(visited(W,Y)), (safe(W,S) ; safe(W,N))) ;
(detectBarrier(X,Y) , avoidBarrierByWest(X,Y), not(detectHoleWest(X,Y)))
))).

goEast(X,Y) :-
E is X+1, S is Y+1, N is Y-1, walkable(E, Y),
(safe(X,Y) ;
(wind(X,Y),
(safe(E,Y) ;
(not(visited(E,Y)), (safe(E,S) ; safe(E,N))) ;
(detectBarrier(X,Y) , avoidBarrierByEast(X,Y), not(detectHoleEast(X,Y)))
))).

/*We prefer to discover new cases*/
betterNorth(X,Y) :-
N is Y-1,
goNorth(X,Y), not(visited(X,N)).

betterSouth(X,Y) :-
S is Y+1,
goSouth(X,Y), not(visited(X,S)).

betterWest(X,Y) :-
W is X-1,
goWest(X,Y), not(visited(W,Y)).

betterEast(X,Y) :-
E is X+1,
goEast(X,Y), not(visited(E,Y)).

goDieInSouth(X,Y):-
S is Y+1,
wind(X,Y), walkable(X,S), not(visited(X,S)).

goDieInNorth(X,Y):-
N is Y-1,
wind(X,Y), walkable(X,N), not(visited(X,N)).

goDieInEast(X,Y):-
E is X+1,
wind(X,Y), walkable(E,Y), not(visited(E,Y)).

goDieInWest(X,Y):-
W is X-1,
wind(X,Y), walkable(W,Y), not(visited(W,Y)).
