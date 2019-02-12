/******************************************************************************/
/*																										*/
/*					Students : Michael Russell          */
/*             Date: 18 April 2000                             					*/
/*					Assignment Number 2  -  Animal Game       							*/
/*					Module: Data Structures & Algorithms(No. 25)							*/
/*					BTEC HND  Software Engineering  -  Group 2							*/
/*					Tutor: R.M Brown																*/
/*																										*/
/******************************************************************************/
#define MAXLEN 64
#define LENGTH 16
#define SUBJECT "animal"
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct NODE{
	char animal [LENGTH];
	char question [MAXLEN];
	struct NODE *left_ptr;
	struct NODE *right_ptr;
}ENTRY_TYP, *ENTRY_PTR_TYP;


// *** FUNCTIONS ***

// Get the details from the user for a new record
void request_input(char *s1, char *s2)
{
	printf("What is the name of the %s you were thinking of?:",SUBJECT);
	gets(s1);
	printf("Enter a question regarding a distinguishing feature:");
	gets(s2);
	return;
}

// Return pointer to new record or NULL if no memory
ENTRY_PTR_TYP new_rec (void)
{
	ENTRY_PTR_TYP ptr;
	if((ptr=(ENTRY_PTR_TYP)malloc(sizeof(ENTRY_TYP))) == NULL)
		fprintf(stderr, "\n Sorry, game aborted, out of memory");
	return(ptr);
}

// Set fields of record to appropraite values
void add_rec(ENTRY_PTR_TYP ptr, char *s1, char *s2)
{
		strcpy(ptr->animal, s1);
		strcpy(ptr->question, s2);
		ptr->left_ptr = NULL;
		ptr->right_ptr = NULL;
		return ;
}

int main (void)
{
	// Function definitions

	ENTRY_PTR_TYP new_rec(void);
	void request_input(char *s1, char *s2);
	void add_rec(ENTRY_PTR_TYP p, char *s1, char *s2);

	// Variable definitions

	int exit_flag = FALSE;
	char new_animal[LENGTH], new_question[MAXLEN];
	char dummy;
	char response;
	ENTRY_PTR_TYP root_ptr, run_ptr, new_ptr;

	if(root_ptr = new_rec())
		add_rec(root_ptr, "fish", "Can it swim?");  // Set up root node with
	else                                           // initial data
		exit(0); // Out of memory

	do
	{
		run_ptr = root_ptr;
		exit_flag = FALSE;
		do
		{
			printf("\n\n\nThink of an %s....\n",SUBJECT);
			do
			{
				printf("\n%s ", run_ptr->question);
				while ((response = tolower(getchar())) != 'y' && response !='n')
				{}
				dummy=getchar(); // dispose of CR in keyboard buffer
				if(response == 'y')
				{
					printf("Is it a %s?", run_ptr->animal);
					while ((response = tolower(getchar())) != 'y' && response !='n')
					{}
					dummy=getchar(); // dispose of CR in keyboard buffer
					if (response == 'y')
					{
						exit_flag = TRUE; // Subject found
						run_ptr = root_ptr;
					}
					else
					{
						if(run_ptr->right_ptr == NULL)
						{
							request_input(new_animal, new_question);
							new_ptr = new_rec();
							if(new_ptr != NULL)
							{
								add_rec(new_ptr, new_animal, new_question);
								run_ptr->right_ptr = new_ptr;
							}
							else
								exit(0); // Out of memory
							run_ptr = root_ptr;
						}
						else
							run_ptr = run_ptr->right_ptr;
					}
				 }
				 else
				 {
					if(run_ptr->left_ptr == NULL)
						{
							request_input(new_animal, new_question);
							new_ptr = new_rec();
							if(new_ptr != NULL)
							{
								add_rec(new_ptr, new_animal, new_question);
								run_ptr->left_ptr = new_ptr;
							}
							else
								exit(0); // Out of memory
							run_ptr = root_ptr;
						}
						else
							run_ptr = run_ptr->left_ptr;
				 }
			 }while(run_ptr != root_ptr);
		}while(exit_flag == FALSE);
		printf("\n\nI have found your animal!");
		printf("\nDo you want to play again? ");
		while ((response = tolower(getchar())) != 'y' && response !='n')
			{}
			dummy=getchar(); // dispose of CR in keyboard buffer
	}while(response == 'y');
   printf("\nThank you for playing");
	return 0;
}

