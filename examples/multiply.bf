#Written by https://github.com/Seng3694
#Can only print single digit numbers

#read a and subtract 48
,>++++++[>++++++++<-]>[<<->>-]<
#read b and subtract 48
,>++++++[>++++++++<-]>[<<->>-]<
#move to a
<<

#(a) (b) (result) (tmp)
# ^

[ #while a not zero
    > #move to b
    [ #while b not zero
        #move to result and add 1
        >+
        #move to tmp and add 1
        >+
        #move back to b and sub 1
        <<-
    ]
    #b is now 0
    #add tmp back to b
    #move to tmp
    >>
    [ #while tmp not zero
        #move to b and add one
        #move to tmp and sub one
        <<+>>-
    ]
    #move to b
    <<
    #move to a and sub 1
    <-
]

#move to result
>>

#add 48 char offset
>++++[<++++++++++>-]<++++++++
#print
.

