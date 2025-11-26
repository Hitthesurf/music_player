# **Definitive guide to `hicpp-signed-bitwise`**

## **Safe Bitwise Operation Rules**

(To fix *signed-bitwise* warnings for `&`, `|`, `^`, `~`, `<<`, `>>`)

### **You must:**

#### **1) Ensure each number is unsigned.**

## **Bitwise AND / OR / XOR (`&`, `|`, `^`)**

### **Notes (`&`, `|`, `^`)**

1. If **both numbers are smaller than `uint32_t`**, the result is **promoted to `int32_t`**.
2. If **one number is `uint32_t`**, the result is **`uint32_t`**.

### **Examples (`&`, `|`, `^`)**

| Expression | Valid? | Output |
|-----------|--------|--------|
| `uint8_t   & uint8_t` | valid | `int32_t` |
| `uint32_t  & uint8_t`  | valid | `uint32_t` |
| `uint8_t   & uint32_t` | valid | `uint32_t` |
| `int8_t    & int8_t`   | invalid | N/A |
| `uint8_t   & int8_t`   | invalid | N/A |

#### **Chained Example**

```cpp
(uint8_t & uint8_t) & uint8_t
→ invalid (because (uint8_t & uint8_t) = int32_t, and int32_t & uint8_t is invalid)
```

## **Shift Operators (`<<`, `>>`)**

### **Notes (`<<`, `>>`)**

1. If the **first element is smaller than `uint32_t`**, the result promotes to **`int32_t`**.
2. If the **first element is `uint32_t`**, the output is **`uint32_t`**.

---

### **Examples (`<<`, `>>`)**

| Expression | Valid? | Output |
|------------|--------|--------|
| `uint8_t  >> uint8_t`    | valid   | `int32_t` |
| `uint32_t >> uint32_t`  | valid   | `uint32_t` |
| `uint8_t  >> uint32_t`   | valid   | `int32_t` |
| `int8_t   >> uint32_t`    | invalid | N/A |
| `uint8_t  >> int32_t`    | invalid | N/A |

#### **Chained Example (`<<`, `>>`)**

```cpp
(uint8_t >> uint8_t) >> uint32_t
→ invalid (because (uint8_t >> uint8_t) = int32_t, and int32_t >> uint32_t is invalid)
```

## **Operator Type Equivalence**

These operators follow the same signed/unsigned validity rules:

```cpp
&, |, ^
<<, >>
~
```

## **More Examples**

### ✔ **Valid Operations**

#### `&`

```cpp
uint8_t & uint8_t → int32_t
uint32_t & uint32_t → uint32_t
uint8_t & uint32_t → uint32_t
uint32_t & uint8_t → uint32_t
```

#### `|`

```cpp
uint8_t | uint8_t → int32_t
uint32_t | uint32_t → uint32_t
uint8_t | uint32_t → uint32_t
uint32_t | uint8_t → uint32_t
```

#### `^`

```cpp
uint8_t ^ uint8_t → int32_t
uint32_t ^ uint32_t → uint32_t
uint8_t ^ uint32_t → uint32_t
uint32_t ^ uint8_t → uint32_t
```

#### `<<`

```cpp
uint8_t << uint8_t → int32_t
uint32_t << uint32_t → uint32_t
uint8_t << uint32_t → int32_t
uint32_t << uint8_t → uint32_t
```

#### `>>`

```cpp
uint8_t >> uint8_t → int32_t
uint32_t >> uint32_t → uint32_t
uint8_t >> uint32_t → int32_t
uint32_t >> uint8_t → uint32_t
```

#### `~`

```cpp
~uint8_t → int32_t
~uint32_t → uint32_t
```

## ❌ **Invalid Operations**

(Any signed type involved)

#### Invalid `&`

```cpp
int8_t & int8_t → int32_t
int32_t & int32_t → int32_t
int8_t & int32_t → int32_t
int32_t & int8_t → int32_t
uint8_t & int8_t → int32_t
int8_t & uint8_t → int32_t
uint8_t & int32_t → int32_t
int32_t & uint8_t → int32_t
uint32_t & int8_t → uint32_t
int8_t & uint32_t → uint32_t
uint32_t & int32_t → uint32_t
int32_t & uint32_t → uint32_t
```

#### Invalid `<<`

```cpp
int8_t << int8_t → int32_t
int32_t << int32_t → int32_t
int8_t << int32_t → int32_t
int32_t << int8_t → int32_t
uint8_t << int8_t → int32_t
int8_t << uint8_t → int32_t
uint8_t << int32_t → int32_t
int32_t << uint8_t → int32_t
uint32_t << int8_t → uint32_t
int8_t << uint32_t → int32_t
uint32_t << int32_t → uint32_t
int32_t << uint32_t → int32_t
```

#### Invalid `~`

```cpp
~int8_t → int32_t
~int32_t → int32_t
```
