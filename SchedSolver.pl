:-include('./prologData.pl').
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
  defineDomains(Vars,1,Domains),
  writeDomains(1,Domains),
  defineConstraints(Vars,Domains),
  label(Vars),
  write(Vars),nl.

writeDomains(VarNumber,[X|Domains]):-
  write('Variable '), write(VarNumber), write(': '),
  write(X), nl,
  VarNumber2 is VarNumber + 1,
  writeDomains(VarNumber2,Domains).

writeDomains(_,[]).

defineVars(Vars):-
  latestStartingHour(N),
  length(Vars,N).

defineDomains([S|Vars],Slot,[L|Tail]):-
  findall([Subject,Group],
  class(Slot,Subject,Group),L),
  length(L,M),
  M >= 1,
  S in 1..M,
  Slot2 is Slot + 1,
  defineDomains(Vars,Slot2,Tail).

defineDomains([S|Vars],Slot,[L|Tail]):-
  findall(Slot,class(Slot,_,_),L),
  length(L,M),
  M =:= 0,
  S #= 0,
  Slot2 is Slot + 1,
  defineDomains(Vars,Slot2,Tail).

defineDomains([],_,[]).

defineConstraints(Vars,Domains):-
  enforceConsistency(Vars,Domains,1),
  onlyOneGroup(Vars,Domains,1).

enforceConsistency(Vars,Domains,Subject):-
  numberOfSubjects(N),
  Subject =< N,
  findall(G,group(Subject,G,_),L),
  forceEqual(Vars,Domains,Subject,L),
  Subject2 is Subject + 1,
  enforceConsistency(Vars,Domains,Subject2).

enforceConsistency(_,_,_).


forceEqual(Vars,Domains,Subject,[G|ListGroups]):-
  findall(Slot,class(Slot,Subject,G),L),
  auxEqual(Vars,Domains,Subject,G,L),
  forceEqual(Vars,Domains,Subject,ListGroups).

forceEqual(_,_,_,[]).

auxEqual(Vars,Domains,Subject,Group,[S|Slots]):-
  iterateThrough(Vars,Domains,Subject,Group,S,Slots),
  auxEqual(Vars,Domains,Subject,Group,Slots).

auxEqual(_,_,_,_,[]).

iterateThrough(Vars,Domains,Subject,Group,First,[X|Rest]):-
  nth1(First,Vars,FirstElement),
  nth1(X,Vars,SecondElement),
  nth1(First,Domains,FirstList),
  nth1(X,Domains,SecondList),
  nth1(FirstIndex,FirstList,[Subject,Group]),
  nth1(SecondIndex,SecondList,[Subject,Group]),
  FirstElement #= FirstIndex #<==> SecondElement #= SecondIndex,
  iterateThrough(Vars,Domains,Subject,Group,First,Rest).

iterateThrough(_,_,_,_,_,[]).

onlyOneGroup(Vars,Domains,CurrentSubject):-
  numberOfSubjects(N),
  CurrentSubject =< N,
  findall(GTheory,group(CurrentSubject,GTheory,1),LTheory),
  auxOnlyOneGroup(Vars,Domains,CurrentSubject,LTheory),
  findall(GLab,group(CurrentSubject,GLab,0),LLab),
  auxOnlyOneGroup(Vars,Domains,CurrentSubject,LLab),
  Subj2 is CurrentSubject + 1,
  onlyOneGroup(Vars,Domains,Subj2).

onlyOneGroup(_,_,_).

auxOnlyOneGroup(Vars,Domains,CurrentSubject,[G|Groups]):-
  findall(S1,class(S1,CurrentSubject,G),L1),
  findall([S2,G2],(member(G2,Groups),class(S2,CurrentSubject,G2)),L2),
  iterateExclusion(Vars,Domains,CurrentSubject,G,L1,L2),
  auxOnlyOneGroup(Vars,Domains,CurrentSubject,Groups).

auxOnlyOneGroup(_,_,_,[]).

iterateExclusion(Vars,Domains,Subject,G1,[X|RestOfSlots],GroupAndSlot):-
  auxIterate(Vars,Domains,Subject,G1,X,GroupAndSlot),
  iterateExclusion(Vars,Domains,Subject,G1,RestOfSlots,GroupAndSlot).

iterateExclusion(_,_,_,_,[],_).

auxIterate(Vars,Domains,Subj,G1,CurrentSlot,[[S2,G2]|RestOfPairs]):-
  nth1(CurrentSlot,Vars,FirstVar),
  nth1(S2,Vars,SecondVar),
  nth1(CurrentSlot,Domains,FirstList),
  nth1(S2,Domains,SecondList),
  nth1(FirstIndex,FirstList,[Subj,G1]),
  nth1(SecondIndex,SecondList,[Subj,G2]),
  /*write('Slot '), write(CurrentSlot), write(' #= '),
  write(FirstIndex), write(' #==> '), write('Slot '),write(S2),
  write(' #\\= '),write(SecondIndex),nl,
  write('Slot '), write(S2), write(' #= '),
  write(SecondIndex), write(' #==> '), write('Slot '),write(CurrentSlot),
  write(' #\\= '),write(FirstIndex),nl,*/
  FirstVar #= FirstIndex #==> SecondVar #\=  SecondIndex,
  SecondVar #= SecondIndex #==> FirstVar #\= FirstIndex,
  auxIterate(Vars,Domains,Subj,G1,CurrentSlot,RestOfPairs).

auxIterate(_,_,_,_,_,[]).




































