:-include('./fixedPredicates.pl').
:-use_module(library(clpfd)).
/*
Format:
subject(number).
theoryGroup(subject,group).
labGroup(subject,group).
class(subject,group,slot).
Where slot numbers go from 1 (8:00-9:00)
to 13 (20:00-21:00) on monday,
14 to 26 on tuesday, etc.
Predicates for directing optimization:
minimizeLeisureTime.
- Minimizes time spent between classes.
earliestHours.
- Minimizes number of hours between 8:00 and the first hour.
latestHours.
- Maximizes number of hours between 8:00 and the first hour.
*/

subject(S):- numberOfSubjects(N), between(1,N,S).


main:-
  defineVars(Vars),
  defineDomains(Vars,1),
  defineConstraints(Vars),
  label(Vars),
  write(Vars),nl.

defineVars(Vars):-
  totalNumberOfSlots(N),
  length(Vars,N).

defineDomains([S|Vars],Slot):-
  findall(Slot,class(Slot,_,_),L),
  length(L,M),
  M >= 1,
  S in 1..M,
  Slot2 is Slot + 1,
  defineDomains(Vars,Slot2).

defineDomains([S|Vars],Slot):-
  findall(Slot,class(Slot,_,_),L),
  length(L,M),
  M =:= 0,
  S in 0,
  Slot2 is Slot + 1,
  defineDomains(Vars,Slot2).

defineDomains([],_).

defineConstraints(Vars):-
  enforceConsistency(Vars,1).

enforceConsistency([S|Vars],Slot):-
  findall([S,G],class(Slot,S,G),L),
  
