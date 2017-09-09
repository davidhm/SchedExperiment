:-include('./prologData.pl').
:-use_module(library(clpfd)).
:- discontiguous
  class/3, group/3.
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
isTheoryGroup(Group):- 0 #= Group mod 10.
isLabGroup(Group):- \+ isTheoryGroup(Group).
groupIndex(Group,_,Index):-
  isTheoryGroup(Group),
  Index #= div(Group,10).
groupIndex(Group,Subject,Index):-
  isLabGroup(Group),
  findall(G,group(Subject,G,0),L),
  sort(L,Sorted),
  nth1(Index,Sorted,Group).

main:-
  defineVars(Vars),
  defineDomains(Vars,1),
  noOverlapping(Vars,1),
  label(Vars),
  write(Vars),
  halt.

main:-
  write('[]'),halt.

defineVars(Vars):-
  numberOfSubjects(N),
  M is 2*N,
  length(Vars,M).

defineDomains([T,L|Vars],Subj):-
  findall(G,group(Subj,G,1),TheoryList),
  length(TheoryList,N),
  T in 1..N,
  findall(G2,group(Subj,G2,0),LabList),
  length(LabList,M),
  M >= 1,
  L in 1..M,
  Subj2 is Subj + 1,
  defineDomains(Vars,Subj2).

defineDomains([T,L|Vars],Subj):-
  findall(G,group(Subj,G,1),TheoryList),
  length(TheoryList,N),
  T in 1..N,
  findall(G2,group(Subj,G2,0),LabList),
  length(LabList,M),
  M #= 0,
  L #= 0,
  Subj2 is Subj + 1,
  defineDomains(Vars,Subj2).

defineDomains([],_).

noOverlapping(Vars,Slot):-
  latestStartingHour(H),
  Slot =< H,
  findall(S-G,class(Slot,S,G),L),
  findall([S1-G1,S2-G2],
  (member(S1-G1,L),member(S2-G2,L), S1 \= S2),Pairs),
  excludeConflicting(Vars,Pairs),
  Slot2 #= Slot + 1,
  noOverlapping(Vars,Slot2).

noOverlapping(_,Slot):-
  latestStartingHour(H),
  Slot > H.

excludeConflicting(Vars,[[S1-G1,S2-G2]|Pairs]):-
  Aux1 #= 1 + (S1-1)*2,
  Aux2 #= 1 + (S2-1)*2,
  nth1(Aux1,Vars,T1),
  nth1(Aux2,Vars,T2),
  isTheoryGroup(G1),
  isTheoryGroup(G2),
  groupIndex(G1,S1,FirstIndex),
  groupIndex(G2,S2,SecondIndex),
  T1 #= FirstIndex #==> T2 #\= SecondIndex,
  excludeConflicting(Vars,Pairs).

excludeConflicting(Vars,[[S1-G1,S2-G2]|Pairs]):-
  Aux1 #= 1 + (S1-1)*2,
  Aux2 #= 2 + (S2-1)*2,
  nth1(Aux1,Vars,T1),
  nth1(Aux2,Vars,L2),
  isTheoryGroup(G1),
  isLabGroup(G2),
  groupIndex(G1,S1,FirstIndex),
  groupIndex(G2,S2,SecondIndex),
  T1 #= FirstIndex #==> L2 #\= SecondIndex,
  excludeConflicting(Vars,Pairs).

excludeConflicting(Vars,[[S1-G1,S2-G2]|Pairs]):-
  Aux1 #= 2 + (S1-1)*2,
  Aux2 #= 1 + (S2-1)*2,
  nth1(Aux1,Vars,L1),
  nth1(Aux2,Vars,T2),
  isLabGroup(G1),
  isTheoryGroup(G2),
  groupIndex(G1,S1,FirstIndex),
  groupIndex(G2,S2,SecondIndex),
  L1 #= FirstIndex #==> T2 #\= SecondIndex,
  excludeConflicting(Vars,Pairs).

excludeConflicting(Vars,[[S1-G1,S2-G2]|Pairs]):-
  Aux1 #= 2 + (S1-1)*2,
  Aux2 #= 2 + (S2-1)*2,
  nth1(Aux1,Vars,L1),
  nth1(Aux2,Vars,L2),
  isLabGroup(G1),
  isLabGroup(G2),
  groupIndex(G1,S1,FirstIndex),
  groupIndex(G2,S2,SecondIndex),
  L1 #= FirstIndex #==> L2 #\= SecondIndex,
  excludeConflicting(Vars,Pairs).

excludeConflicting(_,[]).














































