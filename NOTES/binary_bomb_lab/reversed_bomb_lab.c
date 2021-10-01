// NOTE: this is minimal reverse engineering done to diffuse this bomb. 
//       Hahaha... not absolutely minimal as I just couldn't stop reversing !

// ./bomb input_bomb

void initialize_bomb ();
void sig_handler_func ();

// diffused : "I am just a renegade hockey mom."
void phase_1 (const char *ips) {
    int ret_value;
    
    // user-input string comparison to a hardcoded string
    if (strings_not_equal (ips, "I am just a renegade hockey mom."))
        explode_bomb ();
}


/*
   0x00005555555555cb <+0>:     endbr64 
   0x00005555555555cf <+4>:     push   %rbp
   0x00005555555555d0 <+5>:     push   %rbx
   0x00005555555555d1 <+6>:     sub    $0x28,%rsp
   0x00005555555555d5 <+10>:    mov    %fs:0x28,%rax
   0x00005555555555de <+19>:    mov    %rax,0x18(%rsp)
   0x00005555555555e3 <+24>:    xor    %eax,%eax
   0x00005555555555e5 <+26>:    mov    %rsp,%rsi
   0x00005555555555e8 <+29>:    callq  0x555555555c11 <read_six_numbers>
   
   
=> 0x00005555555555ed <+34>:    cmpl   $0x1,(%rsp)
   0x00005555555555f1 <+38>:    jne    0x5555555555fd <phase_2+50>
   
   0x00005555555555f3 <+40>:    mov    %rsp,%rbx
   0x00005555555555f6 <+43>:    lea    0x14(%rsp),%rbp  rbp = &6
   0x00005555555555fb <+48>:    jmp    0x555555555612 <phase_2+71>
   
        0x00005555555555fd <+50>:    callq  0x555555555be5 <explode_bomb>
        0x0000555555555602 <+55>:    jmp    0x5555555555f3 <phase_2+40>
        0x0000555555555604 <+57>:    callq  0x555555555be5 <explode_bomb>
   
   0x0000555555555609 <+62>:    add    $0x4,%rbx
   0x000055555555560d <+66>:    cmp    %rbp,%rbx
   0x0000555555555610 <+69>:    je     0x55555555561d <phase_2+82>
   
   0x0000555555555612 <+71>:    mov    (%rbx),%eax
   0x0000555555555614 <+73>:    add    %eax,%eax
   0x0000555555555616 <+75>:    cmp    %eax,0x4(%rbx)
   
   0x0000555555555619 <+78>:    je     0x555555555609 <phase_2+62>
   0x000055555555561b <+80>:    jmp    0x555555555604 <phase_2+57>
   0x000055555555561d <+82>:    mov    0x18(%rsp),%rax
   0x0000555555555622 <+87>:    xor    %fs:0x28,%rax
   0x000055555555562b <+96>:    jne    0x555555555634 <phase_2+105>
   0x000055555555562d <+98>:    add    $0x28,%rsp
   0x0000555555555631 <+102>:   pop    %rbx
   0x0000555555555632 <+103>:   pop    %rbp
   0x0000555555555633 <+104>:   retq   
   0x0000555555555634 <+105>:   callq  0x555555555220 <__stack_chk_fail@plt>
End of assembler dump.


// STACK DIGRAM
 * 00000000 00000000 (padding for 16-byte aligned memory reads)
 * 00000000 00000000 (STACK GUARD)
 * 00000000 00000000
 * 00000000 00000000
 * 00000001 00000000 <--- a
 *
 * input string -> "1 2 4 8 16 32"
 */
void phase_2 (const char *ips) {
    int a[6];
    
    read_six_numbers (ips, a);

    // A compiler generated assembly (weirdly generated) loop with pointer arithemetic
    for (i = 0; i < 6; ++i) {
        if (a[i] + a[i] != a[i+1]) {
            explode_bomb ();
        }
    }        
}    

/*
0x0000555555555674 <+59>:    mov    (%rsp),%eax
   0x0000555555555677 <+62>:    lea    0x1b22(%rip),%rdx        # 0x5555555571a0
   0x000055555555567e <+69>:    movslq (%rdx,%rax,4),%rax
   0x0000555555555682 <+73>:    add    %rdx,%rax
   0x0000555555555685 <+76>:    notrack jmpq *%rax
   0x0000555555555688 <+79>:    callq  0x555555555be5 <explode_bomb>
   0x000055555555568d <+84>:    jmp    0x55555555566a <phase_3+49>
   0x000055555555568f <+86>:    mov    $0x274,%eax
   0x0000555555555694 <+91>:    sub    $0x24c,%eax
   0x0000555555555699 <+96>:    add    $0x2b0,%eax
   0x000055555555569e <+101>:   sub    $0x7e,%eax
   0x00005555555556a1 <+104>:   add    $0x7e,%eax
   0x00005555555556a4 <+107>:   sub    $0x7e,%eax
   0x00005555555556a7 <+110>:   add    $0x7e,%eax
   0x00005555555556aa <+113>:   sub    $0x7e,%eax
   0x00005555555556ad <+116>:   cmpl   $0x5,(%rsp)
   0x00005555555556b1 <+120>:   jg     0x5555555556b9 <phase_3+128>
   0x00005555555556b3 <+122>:   cmp    %eax,0x4(%rsp)
   0x00005555555556b7 <+126>:   je     0x5555555556be <phase_3+133>
   0x00005555555556b9 <+128>:   callq  0x555555555be5 <explode_bomb>
   0x00005555555556be <+133>:   mov    0x8(%rsp),%rax
   0x00005555555556c3 <+138>:   xor    %fs:0x28,%rax
   0x00005555555556cc <+147>:   jne    0x555555555710 <phase_3+215>
   0x00005555555556ce <+149>:   add    $0x18,%rsp
   0x00005555555556d2 <+153>:   retq   
   0x00005555555556d3 <+154>:   mov    $0x0,%eax
*/
void phase_3 (const char *ips) {
    
    int a[2];

    if (sscanf (ips, "%d %d", &a[0], &a[1]) <= 1) explode_bomb ();
    
    if ((unsgined int )a[0] > 7) explode_bomb ();
    
    if (a[0] > 5) explode_bomb ();
    
    // 0xffffffe6 is 26 in 2's complement form (-26 is signed version)
    if ((unsigned int )a[1] != 0xffffffe6) explode_bomb ();     
    
}

/* 
 * ip1 = 0
 * a = 0
 * b = 0xe
 * 
 * I needed to check the mathematical equation to diffuse this one - 
 * We need to find a value of ip1 such that func4() returns 10 to phase_4()
 * (its caller routine).
 * 
 *      f4(x, 0, 14) => (14-0)/2 + 0 = [7]
 *               |  
 *               |----> (x > 7) f(x, [7]-1, 14) ----> (14-6)/2 + 6 = 10 -> means will return [10 + [7]] 
 *               |----> (x < 7) f(x, 0, [7]-1)  ----> (6-0)/2 + 0 = 3 -> means will return [3 + [7]] which fortunately is equal to 10. So, x should be equal to this expression evaluation, i.e. 3
 * 
 * Then we can just check into what branch will make the value of ebx equal to
 * 0xa which is getting checked by the caller (phase_4).
 *
int func4 (int ip1, int a, int b) {
    signed int ebx, eax;
    
    ebx = eax = (b - a);
    ebx = ((ebx >> 0x1f + eax) >> 1) + a;       // ebx evaluates to -> 0x7
    
marker:
    if (ebx > ip1) {        
        b = rbx - 1;
        func4 (ip1, a, b);
        ebx += eax;
        goto ret;
    }
    
    if (ebx < ip1) {
        a = rbx + 1;
        func4 (ip1, a, b);
        ebx += eax;
        goto ret;
    }
  
ret:
    return ebx;
    
}
*/

// Mathematical expression (expr) is *(rbp+4) while debugging on Windbg
func4 (int x, int a, int b) {

	int eax = (((signed qword typecast)(b - a)) - a)/2;
	int expr = ecx = a + eax;
	

	// base case
	if (expr == x) {
		return expr;
	}
	 
	if (expr < x) {
		// 0x00007ff603771f9a
		eax = func4 (x, expr + 1, b);
	}	

	else {
		// 0x00007ff603771f7a:
		eax = func4 (x, a, expr - 1);
	}

	eax += expr 
	return eax;
}



/* 
 * 0000000 0000000  (alignment paddding)
 * 0000000 0000000  (STACK GUARD)
 * 0000000 0000000  <--- rsp
 * 
 * a[0] = 3 (a[0] < 0xe)
 * a[1] = 10
 */
void phase_4 (const char *ips) {
                            /* 8 bytes alignment for optimized memory reads */
    unsigned int a[2];      /* covering 0x10 bytes */
    
    if (sscanf (ips, "%d %d", &a[0], &a[1]) != 2) explode_bomb();
    
    if ( *((unsigned int *)a) > 0xe) {  /* compare a QWORD value at address 'a' */
        explode_bomb ();
    }
    
    if (func4(a[0], 0, 0xe) != 0xa && a[1] != 0xa) explode_bomb ();
// 
}


/*
 * (uint8_t) a[0] < 15  (6)
 * 
 * 
 * (gdb) b *phase_5+80
 * (gdb) b *phase_5+95
 * (gdb) x/20xw $rsi
0x5555555571c0 <array.3471>:    0x0000000a      0x00000002      0x0000000e      0x00000007
0x5555555571d0 <array.3471+16>: 0x00000008      0x0000000c      0x0000000f      0x0000000b
0x5555555571e0 <array.3471+32>: 0x00000000      0x00000004      0x00000001      0x0000000d
0x5555555571f0 <array.3471+48>: 0x00000003      0x00000009      0x00000006      0x00000005
0x555555557200: 0x79206f53      0x7420756f      0x6b6e6968      0x756f7920
 *
 * Index of this array is being stored in rax, we have to reach index 6, 
 * i.e. location of 0xf to end the iterating loop while taking care that the loop 
 * has to iterate exactly 15 (0xf is the value being compared with counter 
 * edx register). Therefore, starting backwards, to reach (rax = 0xf), we need to
 * chain the indexes being stored in eax the below given way -
 *
 * 6 (0xf), e, 2, 1, a, 0, 8, 4, 9, d, b, 7, 3, c, 5, 0xf
 * 
 * input: 5 115
 */
void phase_5 (const char *ips) {
    int a[2];
    
    if (sscanf (ips, "%d %d", a[0], a[1]) <= 1) explode_bomb();
    
    a[0] = a[0] & 0xf;
    if (a[0] == 0xf) explode_bomb();
    
    eax = (uint8_t )a[0];
    edx = ecx = 0;
    do {
        ++edx;                              // edx stores number of times this loop iterates
        eax = *(0x5555555571c0 + eax*4);    // "\n"(0xa) is stored @ 0x5555555571c0
        ecx += eax;
        
    } while (eax != 0xf);
    
    a[0] = 0xf;          
    if (edx != 0xf) explode_bomb ();        // if the above loop didn't iterate 15 times, explode_bomb()
    
    if (a[1] != ecx) explode_bomb ();       // ecx is 115(0x73) till we reach this point.
}


/* 
 * 00000000000000   alignment padding
 * 00000000000000   (STACK CANARY)
 * 00000000000000
 * 00000000000000
 * 00000000000000
 * 00000000000000
 * 00000000000000
 * 00000000000000
 * 00000000000000
 * 00000000000000
 * 00000000000000
 * 00000000000000   <-- rsp, rsi, r13, r12, rbp
 * 
 * 
 * Every input value must be within the range of [0-6] without any duplication.
 * [0-6] [0-5] [0-4] [0-3] [0-2] [0-1]
 
 
struct node {
    int data;           // ???? this is getting compared for checks
    int num;
    struct node *next;
}
  
0x7fffffffdec0: 0x0000000200000001      0x0000000400000003
0x7fffffffded0: 0x0000000600000005      0x0000555555559830  <- i/p "1 2 3 4 5 6"
0x7fffffffdee0: 0x0000555555559200      0x0000555555559210  <- list nodes
0x7fffffffdef0: 0x0000555555559220      0x0000555555559230
0x7fffffffdf00: 0x0000555555559240      0x0000555555559110
0x7fffffffdf10: 0x00005555555596a0      0xd8bb7f101bd54500
0x7fffffffdf20: 0x00007fffffffe038      0x0000555555556a10
0x7fffffffdf30: 0x0000555555555360      0x00007fffffffe030
0x7fffffffdf40: 0x0000000000000000      0x0000555555555543

 */
void phase_6 (const char *ips) {
    
    int nums[6];
    struct node nodes[6];
    int *ptr = &nums[0];
    
    read_six_numbers (ips, nums);
    

    int i = 1;      // r14d, while ptr is r13
    while ((unsigned int )(*ptr - 1) <= 5) {    // phase_6+94
    
        if (i > 5) {     // termination condition for outer loop: r14d
            // phase_6+120
            // create a linked list from user input storing all node addresses
            // on stack just after space allocated for user input.
            

            // rsi is index into nodes[]
            // eax is count
            // ecx = current number
            // rdx = current node
            for (int rsi = 0 ; rsi != 6; ++rsi) {
                // basically creates/adds all nodes onto the allocated memory on 
                // stack (i.e. @ nodes[])
                
                ecx = nums[rsi];    // number
                eax = 1;            // count
                rdx = head_node;    // head node element
                
                if (ecx > 1) {
                    do {                // phase_6+145
                        rdx = rdx->next;
                        ++eax;
                    } while (ecx != eax);
                } 
                
                // phase+156
                nodes[rsi] = rdx;
                ++rsi;
            }
            
            // phase_6+171: link all nodes on stack (create a linked list)
            nodes[0]->next = nodes[1];
            nodes[1]->next = nodes[2]
            nodes[2]->next = nodes[3];
            nodes[3]->next = nodes[4];
            nodes[4]->next = nodes[5];
            nodes[5]->next = 0;
        
            // phase_6+229: ACTUAL sanity check
            // the 'data' member of struct node is a value which we do not control
            // but the order of arrangment of nodes is what we can control
            // here, nodes should be created in descending order of their values
            // stored in 'data' member.
            // It seems that every number we enter from 1-6 is having predefined 
            // value for 'data' member. The order in which we enter values
            //
            // (gdb) x/28xw 0x0000555555559200
            // 0x555555559200 <node1>: 0x00000212      0x00000001      0x55559220      0x00005555
            // 0x555555559210 <node2>: 0x000001c2      0x00000002      0x55559220      0x00005555
            // 0x555555559220 <node3>: 0x00000215      0x00000003      0x55559230      0x00005555
            // 0x555555559230 <node4>: 0x00000393      0x00000004      0x55559240      0x00005555
            // 0x555555559240 <node5>: 0x000003a7      0x00000005      0x55559210      0x00005555
            //
            // Here are the values associated with each user input number:
            // 1: 0x212, 2:0x1c2, 3:0x215, 4:0x393, 5:3a7, 6:0x200
            //
            // In descending order:
            // 5 4 3 1 6 2
            
            node_ptr = head;
            for (int i = 5; i != 0; --i) {
                if (node_ptr->data < node_ptr->next->data)
                    explode_bomb ();
                node_ptr = node_ptr->next;
            }
        }
        
        // this loop ensures that no duplicate value is entered by user.
        // phase_6+70
        // here j is rbx (rbx = r14d)
        for (int j = i /* rbx = r14 */; j <= 5; ++j) {
            if (*ptr == nums[j]) {
                explode_bomb ();
            }
        }
        
        ++i;        // ++r14d; modification expression for outer loop
        ++ptr;      // r13 += 4;
    }
    explode_bomb ();    // if (present_element > 5)
    
}
    
    
    
/* Copy the below content in an input file (to be supplied as (argv[1]))  
   
I am just a renegade hockey mom.
1 2 4 8 16 32
1 -26
3 10
5 115
5 4 3 1 6 2
*/
int main (int argc, char **argv) {

    char *ips;          // this is the input string
    
    // check for command line args
    // use argv[1] (if provided) as input FILE *, else use stdin to take inputs
    if (argc == 1) {
        infile = stdin;
    }
    rbx = argv;
    if (argc == 2) {        // infile = input FILE *
        infile = fopen (argv[1], 0x72);
        if (!infile) {
            fprintf (stdout, "%s: Error: Couldn't open %s\n", argv, argv[1]);
            exit (8);
        }
    }
    else {
        fprintf (stdout, "Usage: %s [<input_file>]\n", argv[0]);
        exit (8);
    }
        
    initialize_bomb ();     // reversed 
    puts ("Welcome to my fiendish little bomb. You have 6 phases with");
    puts ("which to blow yourself up. Have a nice day!");
    
    ips = read_line ();
    phase_1 (ips);
    phase_defused ();
    puts ("Phase 1 defused. How about the next one?");
    
    ips = read_line ();
    phase_2 (ips);
    phase_defused ("That's number 2.  Keep going!");
    puts ();
    
    ips = read_line ();
    phase_3 (ips);
    phase_defused ("Halfway there!");
    puts ();
    
    ips = read_line ();
    phase_4 (ips);
    phase_defused ("So you got that one.  Try this one.");
    puts ();

    ips = read_line ();
    phase_5 (ips);
    phase_defused ("Good work!  On to the next...");
    puts ();
    
    ips = read_line ();
    phase_6 (ips);
    phase_defused ("Congratulations! You've defused the bomb!");
    puts ();
    
}


// takes 7 numbers as input in &nums[0] via sscanf();
void read_six_numbers (const char *ips, int *nums) {
    /* rdi = nums
     * rsi = "%d %d %d %d %d %d"
     * rdx = &num[0] 
     * rcx = &num[1] (num + 0x4)
     * r8d = &num[2] (num + 0x8)
     * r9d = &num[3] (num + 0xc)
     * 
     * stack HIGH addresses ------
     *          00000000 
     *          00000000                 (sub $0x8, %rsp)
     *          &num[5] (num + 0x14)
     * rsp ->   &num[4] (num + 0x10)
     * stack LOW addresses --------
     */
    int count = sscanf (ips, "%d %d %d %d %d %d", &num[0], &num[1], &num[2], &num[3], &num[4], &num[5]);
    if (count <= 5 )
        explode_bomb ();
}


// returns 0 if str1[0] == '\x00' or str1 & str2 are the same.
int strings_not_equal (const char *str1, const char *str2) {
    // push callee-saved registers (r12, rbp, rbx)
    // str1 is out input string
    rbx = str1;
    rbp = str2;
    
    // if string lengths differ, return 1
    if (string_length (str1) != string_length (str2))
        return 1;
    
    if (str1[0] == 0)       // This probably can't happen due to read_line ();
        return 0;
    
    // weird way of comparing 2 strings #_#
    i = 0;
again:
    if (str1[i] != 0) {
        if (str1[i] != str2[i]) {
            return 1;
        }
        else {
            ++i;
            goto again;
        }
    }
    return 0;
}   


// Sets ups signal handler to catch SIGINT (keyboard interrupt) from user and exit(0x10) 
void initialize_bomb () {
    signal (2, sig_handler_func);       // sig #2 : SIGINT
}
void sig_handler_func () {
    puts ("So you think you can stop the bomb with ctrl-c, do you?");
    sleep (3);
    puts ("Well...");
    fflush (stdout);
    sleep (1);
    puts ("OK. :-)");
    exit (0x10);
}
