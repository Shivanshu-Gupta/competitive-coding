# References

- Bit Twiddling Hacks page: http://graphics.stanford.edu/~seander/bithacks.html
- Bit Arrays: http://stackoverflow.com/questions/2525310/how-to-define-and-work-with-an-array-of-bits-in-c

# C++ Bitwise Operators

| Op   | Meaning             |
| ---- | ------------------- |
| &    | bitwise and         |
| \|   | bitwise or          |
| ^    | bitwise xor         |
| ~    | bitwise not         |
| <<   | bitwise shift left  |
| >>   | bitwise shift right |

# Bit Array

```
#define ClearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )
#define TestBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )
#define SetBit(A,k) 	( A[(k/32)] |= (1 << (k%32)) )
```

# Useful Expressions

| Expression                          | Use                                 | Remarks                                          |
| ----------------------------------- | ----------------------------------- | ------------------------------------------------ |
| `(x & 1) ? odd : even`              | Test if the integer is even or odd. |                                                  |
| `(x && !(x & x-1)) ? yes : no`      | Test if $x = 2^k$                   |                                                  |
| `(x && (x & (-x) == x)) ? yes : no` | Test if $x = 2^k$                   | Uses the trick for isolation of rightmost 1-bit. |
| `y = x<<n`                          | Multiplication by $2^n$             | use this to multiply by any number               |
| `(x ^ y) < 0 ? different : same`    | Test if x, y have same signs        |                                                  |
| `y = x^1`                           | 2k to 2k+1 and vice versa           | Toggling the last/rightmost/0-th bit             |
| `y = ~x + 1`                        | two's complement                    | useful with unsigned integers.                   |
| `y = -x`                            | two's complement                    |                                                  |
| `j & (N - 1)`                       | Compute `mod(j, N) for N = 2^k`     | faster than `j%N` and also works for `j < 0`     |

## Operations on n-th bit

| Expression              | Use                  |
| ----------------------- | -------------------- |
| `y = x | (1<<n)`        | **Set** n-th bit     |
| `y = x & ~(1<<n)`       | **Unset** n-th bit   |
| `y = x ^ (1<<n)`        | **Toggle** n-th bit  |
| `y = x & (1<<n)`        | **Isolate** n-th bit |
| `x & (1<<n) ? yes : no` | **Test** n-th bit    |

## Operations related to rightmost bit (can also use the ops for n-th bit)

| Expression      | Use   |
| --------------- | ----- |
| `y = x | (x^1)` | Set   |
| `y = x & (x^1)` | Unset |

## Operations related to rightmost 1-bit (let it be the k-th bit)

| Expression      | Use                                  |
| --------------- | ------------------------------------ |
| `x-1`           | flip n-th bits to the right (n <= k) |
| `-x`            | flip n-th bits to the left (n > k)   |
| `y = x & (x-1)` | **Unset**                            |
| `y = x & (-x)`  | **Isolate**                          |
| `y = x | (x-1)` | **Right Propagate**                  |

#### Examples:

```
10111100     (x)
10111011     (x-1)   - flip n-th bits to the right (n <= k)
01000100     (-x)    - flip n-th bits to the left (n > k)

Unset:
     10111100  (x)
 &   10111011  (x-1)
     --------
     10111000

Isolation:
     10111100  (x)
 &   01000100  (-x)
     --------
     00000100

Right propagation 
     10111100  (x)
 |   10111011  (x-1)
     --------
     10111111
```


## Useful Properties related to rightmost 0-bit (let it be the k-th bit)

| Expression       | Use                                    |
| ---------------- | -------------------------------------- |
| `x+1`            | flip n-th bits to the right (`n <= k`) |
| `y = ~x & (x+1)` | **Isolate**                            |

#### Examples:

```
10001111     (x)
10010000     (x+1)   - flip n-th bits to the right (n <= k)

Isolate:
     01110000  (~x)
 &   10010000  (x+1)
     --------
     00010000

```

# GCC BUILTINS

| Builtin                                    | Name                             | Use                                                          |
| ------------------------------------------ | -------------------------------- | ------------------------------------------------------------ |
| `__builtin_ffs (int x)`                    | Find First Set                   | Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero. |
| `__builtin_clz (unsigned int x)`           | Count Leading Zeroes             | Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined. |
| `__builtin_ctz (unsigned int x)`           | Count Trailing Zeroes            | Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined. |
| `__builtin_popcount (unsigned int x)`      | Pop Count                        | Returns the number of 1-bits in x.                           |
| `__builtin_parity (unsigned int x)`        | Parity                           | Returns the parity of x, i.e. the number of 1-bits in x modulo 2. |
| `__builtin_abcl ([unsigned] long x)`       | `__builtin_abc()` for long.      |                                                              |
| `__builtin_abcll ([unsigned] long long x)` | `__builtin_abc()` for long long. |                                                              |

#### Examples

```
int a=20; //10100

//trailing zeroes
cout<<__builtin_ctz(a)<<endl;   	// gives 2
cout<<__builtin_ctz(a<<4)<<endl;    // gives 6

//leading zeroes
cout<<__builtin_clz(a)<<endl;   	// gives 27
cout<<__builtin_clz(a>>4)<<endl;    // gives 31

cout<<__builtin_clz(0)<<endl;   	// gives 32
```