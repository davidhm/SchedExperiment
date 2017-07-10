:-include('./prologData.pl').
slotsPerDay(S):-
    latestStartingHour(N),
    earliestStartingHour(M),
    S is N - M + 1.
totalNumberOfSlots(N):-
    latestDay(P),
    earliestDay(Q),
    N is P - Q + 1.
