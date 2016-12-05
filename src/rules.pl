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

/*Choose next case*/
goNorth(X,Y) :-
N is Y-1, W is X-1, E is X+1, walkable(X, N),
(safe(X,Y) ;
(wind(X,Y),
  (safe(X,N) ;
   (not(visited(X,N)), (safe(E,N) ; safe(W,N)))
))).

goSouth(X,Y) :-
S is Y+1, W is X-1, E is X+1, walkable(X, S),
(safe(X,Y) ;
(wind(X,Y),
  (safe(X,S) ;
   (not(visited(X,S)), (safe(E,S) ; safe(W,S)))
))).

goWest(X,Y) :-
W is X-1, S is Y+1, N is Y-1, walkable(W, Y),
(safe(X,Y) ;
(wind(X,Y),
  (safe(W,Y) ;
   (not(visited(W,Y)), (safe(W,S) ; safe(W,N)))
))).

goEast(X,Y) :-
E is X+1, S is Y+1, N is Y-1, walkable(E, Y),
(safe(X,Y) ;
(wind(X,Y),
  (safe(E,Y) ;
   (not(visited(E,Y)), (safe(E,S) ; safe(E,N)))
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

/*TODO:
  .w   .wH
  wHw  w.w
  .w.  Hw.
*/
