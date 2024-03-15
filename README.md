# `C-code-formatter`

A command line utility tool that quickly formats your `C` code for you, (so that you don't have to)

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

1. split the entire code into lines
2. each line may consist of either a `{` **OR** a `}` **OR** a line ending with a semicolon;
3. one by one feed the lines into a tree (each line is a node, which has sibling or children)
    - when you find a `{` add to the child of the current line (node)
    - when you find another line ending with a semicolon; add to the sibling of the current line
    - when you find a `}` finish feeding the tree (or subtree)


## up next

- [ ] Handle comments
