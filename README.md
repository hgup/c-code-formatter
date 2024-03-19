# `C-code-formatter`

A command line utility tool that quickly formats your `C` code for you, (so that you don't have to)

## Usage
```bash
make # to build
format file1.c file2.c ... # enter files you want to format
```

> [!NOTE]
> A requirement is that your code should be syntatically correct


# how it works?

Let's go through some definitions that makes the discussion easier
### definitions:

*Formatting characters*: These include 
-   ` `     (spaces), 
-   `    `  (tabs `\t`)

*indentation depth* (ID): It is the number of indents required to logically place a block of text at its nest-level.
An example would explain better

```c
while(a<10)     // this line has ID = 0
{
    a++;                        // ID = 1
    for(int i = 1; i < a; i++)  // ID = 1
    {
        if(i%2 == 0)            // ID = 2
            printf("Done!%d",i);// ID = 3

    }
    printf("end");              // ID = 1
}
```

## STEP 1: REMOVE ALL FORMATTING

First it removes all the existing formatting of the code adhering to some **rules**


### rules:

1. Don't touch anything between subsequent quotation marks(`"`)
2. Remove all existing *formatting characters* before and after `{`, `}`, `;`, `=`, `+`, `-`, `%`, `*`, `/`, `(`, `)`
3. Change all remaining **multiple** spaces or tabs to __single spaces__
4. When you have a line starting with `#` don't remove the `\n` at the end 

## STEP 2: ADD REQUIRED FORMATTING CHARACTERS

### rules (for newlines):

1. put `\n` (newlines) before and after `{`, `}`
2. put `\n` (newline) after `;` (except in `for(...)` loop blocks)
3. **if** you find a `if(...)`, `while(...)` or `for(...)` block without a following `{`, then add a `\n\t`(newline followed by a tab)

### method (for indentation):

1. identify the lines and start pushing them as siblings in a tree
2. when you find a `{` tag, create a child and start pushing the next lines as sibling of that subtree
3. when you find a `}` tag, go back to the parent tree and continue adding the next lines as siblings

### printing

1. print each line on the tree preceding with indents
2. when you find no children, continue printing the next sibling with the same number of indents
3. when you find children, print the current line and start printing all of the children with +1 indents

> The number of indents to be given is nothing but the depth of the tree, so during the recursive call, keeping track of the depth of the tree will be sufficient to find out how many indents to print.


## up next

- [ ] Handle comments

