:- dynamic(light/2).
:- dynamic(poop/2).
:- dynamic(walkable/2).
:- dynamic(wind/2).
:- dynamic(visited/2).
:- dynamic(shooted/2).

portal(X,Y) :- light(X,Y).
runOut(X,Y) :- portal(X,Y).

setVisited(X,Y) :- assert(visited(X,Y)).
setWalkable(X,Y) :- assert(walkable(X,Y)).
setPoop(X,Y) :- assert(poop(X,Y)).
setShooted(X,Y) :- assert(shooted(X,Y)).
removeLight(X,Y) :- retract(light(X,Y)).
removePoop(X,Y) :- retract(poop(X,Y)).
removeWalkable(X,Y) :- retract(walkable(X,Y)).
removeWind(X,Y) :- retract(wind(X,Y)).
removeVisited(X,Y) :- retract(visited(X,Y)).
removeShooted(X,Y) :- retract(shooted(X,Y)).

safe(X,Y) :- visited(X,Y), not(poop(X,Y)), not(wind(X,Y)).

shootNorth(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
poop(X,Y), walkable(X,N), not(shooted(X,N)), not(visited(X,N)).

shootSouth(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
poop(X,Y), walkable(X,S), not(shooted(X,S)), not(visited(X,S)).

shootWest(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
poop(X,Y), walkable(W,Y), not(shooted(W,Y)), not(visited(W,Y)).

shootEast(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
poop(X,Y), walkable(E,Y), not(shooted(E,Y)), not(visited(E,Y)).

goNorth(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
((safe(X,Y), walkable(X, N)) ;
(wind(X,Y), safe(X,N))).

goSouth(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
((safe(X,Y), walkable(X, S)) ;
(wind(X,Y), safe(X,S))).

goWest(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
((safe(X,Y), walkable(W, Y)) ;
(wind(X,Y), safe(W,Y))).

goEast(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
((safe(X,Y), walkable(E, Y)) ;
(wind(X,Y), safe(E,Y))).

betterNorth(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
goNorth(X,Y), not(visited(X,N)).

betterSouth(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
goSouth(X,Y), not(visited(X,S)).

betterWest(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
goWest(X,Y), not(visited(W,Y)).

betterEast(X,Y) :-
N is Y-1, W is X-1, S is Y+1, E is X+1,
goEast(X,Y), not(visited(E,Y)).
