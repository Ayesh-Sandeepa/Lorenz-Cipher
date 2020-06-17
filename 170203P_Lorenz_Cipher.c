//changed percentage = 49.98%

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// wheel settings for the Lorenz cipher
char chi1[41] = {1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1};
char chi2[31] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0};
char chi3[29] = {1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0};
char chi4[26] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1};
char chi5[23] = {1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0};

char psi1[43] = {1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0};
char psi2[47] = {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0};
char psi3[51] = {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1};
char psi4[53] = {0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1};
char psi5[59] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0};

char mu1[61] = {0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0};
char mu2[37] = {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};

// wheel rotation (shift register operation)
void move_chi_pos(int chi_pos[5])
{
    chi_pos[0] = (chi_pos[0] + 1) % 41;
    chi_pos[1] = (chi_pos[1] + 1) % 31;
    chi_pos[2] = (chi_pos[2] + 1) % 29;
    chi_pos[3] = (chi_pos[3] + 1) % 26;
    chi_pos[4] = (chi_pos[4] + 1) % 23;
}

void move_psi_pos(int psi_pos[5])
{
    psi_pos[0] = (psi_pos[0] + 1) % 43;
    psi_pos[1] = (psi_pos[1] + 1) % 47;
    psi_pos[2] = (psi_pos[2] + 1) % 51;
    psi_pos[3] = (psi_pos[3] + 1) % 53;
    psi_pos[4] = (psi_pos[4] + 1) % 59;
}

void move_mu_pos1(int *mu_pos1)
{
    *mu_pos1 = (*mu_pos1 + 1) % 61;
}

void move_mu_pos2(int *mu_pos2)
{
    *mu_pos2 = (*mu_pos2 + 1) % 37;
}

// utility functions
void print_chi(int chi_pos[5])
{
    printf("%i ", chi1[chi_pos[0]]);
    printf("%i ", chi2[chi_pos[1]]);
    printf("%i ", chi3[chi_pos[2]]);
    printf("%i ", chi4[chi_pos[3]]);
    printf("%i ", chi5[chi_pos[4]]);
    printf("| ");
}

void print_psi(int psi_pos[5])
{
    printf("%i ", psi1[psi_pos[0]]);
    printf("%i ", psi2[psi_pos[1]]);
    printf("%i ", psi3[psi_pos[2]]);
    printf("%i ", psi4[psi_pos[3]]);
    printf("%i ", psi5[psi_pos[4]]);
    printf("| ");
}

void print_mu(int mu_pos[2])
{
    printf("%i ", mu1[mu_pos[0]]);
    printf("%i ", mu2[mu_pos[1]]);
    printf("| ");
}

void encrypt(int plain[5], int keyStrean[5])
{
}

//function to generate key stream
char *generateKeyStream(int chi_pos[5], int psi_pos[5], int mu_pos[2])
{
    static char K[5];

    char clock_mu_wheel;
    char clock_psi_wheel;

    // 1. Encrypting each 5-bit word at time t
    //    K_t = chi_t^i \xor psi_{t_chi}^i
    K[0] = chi1[chi_pos[0]] ^ psi1[psi_pos[0]];
    K[1] = chi2[chi_pos[1]] ^ psi2[psi_pos[1]];
    K[2] = chi3[chi_pos[2]] ^ psi3[psi_pos[2]];
    K[3] = chi4[chi_pos[3]] ^ psi4[psi_pos[3]];
    K[4] = chi5[chi_pos[4]] ^ psi5[psi_pos[4]];

    // print_chi(chi_pos);
    // print_psi(psi_pos);
    // print_mu(mu_pos);

    clock_mu_wheel = 0;
    clock_psi_wheel = 0;

    // 2. clock ticked as t = t+1
    //    move all chi wheels
    move_chi_pos(chi_pos);
    //    move first mu wheel
    move_mu_pos1(&mu_pos[0]);

    // 3. check for mu wheel rotation
    if (mu1[mu_pos[0]] == 1)
        clock_mu_wheel = 1;
    //    move mu wheels
    if (clock_mu_wheel == 1)
    {
        move_mu_pos2(&mu_pos[1]);
    }

    // 4. check for psi wheel rotation
    if (mu2[mu_pos[1]] == 1)
        clock_psi_wheel = 1;
    //    move psi wheels
    if (clock_psi_wheel == 1)
        move_psi_pos(psi_pos);

    // 5. output K_t
    for (int i = 0; i < 5; i++)
    {
        //printf("%i ",K[i]);
    }

    return K;
}

void main()
{
    FILE *fp = fopen("plain.txt", "r");
    FILE *enc = fopen("cipherText1.txt", "w");
    FILE *keyStr = fopen("keyStream1.txt", "w");

    
    char str[50];
    char buff[5];

    float totalBits = 0, changedBits = 0;

    // Starting positions of wheels
    int chi_pos[5] = {0, 0, 0, 0, 0};
    int psi_pos[5] = {0, 0, 0, 0, 0};
    int mu_pos[2] = {0, 0};

    char encText[5];
    char *k1;

    //read input file fifty characters by fifty characters from file plain.txt
    while (fgets(str, 50, fp) != NULL)
    {
        //get a letter by letter from each word and encryptng each letter 
        for (int i = 0; i < strlen(str); i++)
        {
            char letter = str[i];
            printf("%c: ", letter);
            if (str[i] == 'a' || str[i] == 'A' || str[i] == '-')
            {
                strcpy(buff, "00011"); 
            }
            else if (str[i] == 'b' || str[i] == 'B' || str[i] == '?')
            {
                strcpy(buff, "11001"); 
            }
            else if (str[i] == 'c' || str[i] == 'C' || str[i] == ':')
            {
                strcpy(buff, "01110"); 
            }
            else if (str[i] == 'd' || str[i] == 'D')
            {
                strcpy(buff, "01001"); 
            }
            else if (str[i] == 'e' || str[i] == 'E' || str[i] == '3')
            {
                strcpy(buff, "00001"); 
            }
            else if (str[i] == 'f' || str[i] == 'F' || str[i] == '!')
            {
                strcpy(buff, "01101"); 
            }
            else if (str[i] == 'g' || str[i] == 'G' || str[i] == '&')
            {
                strcpy(buff, "11010"); 
            }
            else if (str[i] == 'h' || str[i] == 'H')
            {
                strcpy(buff, "10100"); 
            }
            else if (str[i] == 'i' || str[i] == 'I' || str[i] == '8')
            {
                strcpy(buff, "00110"); 
            }
            else if (str[i] == 'j' || str[i] == 'J')
            {
                strcpy(buff, "01011"); 
            }
            else if (str[i] == 'k' || str[i] == 'K' || str[i] == '(')
            {
                strcpy(buff, "01111"); 
            }
            else if (str[i] == 'l' || str[i] == 'L' || str[i] == ')')
            {
                strcpy(buff, "10010"); 
            }
            else if (str[i] == 'm' || str[i] == 'M' || str[i] == '.')
            {
                strcpy(buff, "11100"); 
            }
            else if (str[i] == 'n' || str[i] == 'N' || str[i] == ',')
            {
                strcpy(buff, "01100"); 
            }
            else if (str[i] == 'o' || str[i] == 'O' || str[i] == '9')
            {
                strcpy(buff, "11000"); 
            }
            else if (str[i] == 'p' || str[i] == 'P' || str[i] == '0')
            {
                strcpy(buff, "10110"); 
            }
            else if (str[i] == 'q' || str[i] == 'Q' || str[i] == '1')
            {
                strcpy(buff, "10111"); 
            }
            else if (str[i] == 'r' || str[i] == 'R' || str[i] == '4')
            {
                strcpy(buff, "01010");
            }
            else if (str[i] == 's' || str[i] == 'S' || str[i] == '\'')
            {
                strcpy(buff, "00101"); 
            }
            else if (str[i] == 't' || str[i] == 'T' || str[i] == '5')
            {
                strcpy(buff, "10000"); 
            }
            else if (str[i] == 'u' || str[i] == 'U' || str[i] == '7')
            {
                strcpy(buff, "00111"); 
            }
            else if (str[i] == 'v' || str[i] == 'V' || str[i] == '=')
            {
                strcpy(buff, "11110"); 
            }
            else if (str[i] == 'w' || str[i] == 'W' || str[i] == '2')
            {
                strcpy(buff, "10011"); 
            }
            else if (str[i] == 'x' || str[i] == 'X' || str[i] == '/')
            {
                strcpy(buff, "11101"); 
            }
            else if (str[i] == 'y' || str[i] == 'Y' || str[i] == '6')
            {
                strcpy(buff, "10101"); 
            }
            else if (str[i] == 'z' || str[i] == 'Z' || str[i] == '+')
            {
                strcpy(buff, "10001");
            }
            else if (str[i] == ' ')
            {
                strcpy(buff, "00100");
            }
            else if (str[i] == '\n')
            {
                strcpy(buff, "00010"); 
            }
            else
            {
                strcpy(buff, "00000");
            }

            //printing the read letter to concole
            for (int p = 0; p < 5; p++)
            {
                printf("%c", buff[p]);
            }
            printf(" | ");

            //get the generated key stream
            k1 = generateKeyStream(chi_pos, psi_pos, mu_pos);

            //writing the generated key stream to keyStream.txt file and printing to concole
            printf("Key Stream: ");
            for (int p = 0; p < 5; p++)
            {
                fprintf(keyStr, "%i", k1[p]);
                printf("%i", k1[p]);
            }
            printf(" | ");
            fprintf(keyStr, " ");

            //encrypting the letter
            encText[0] = k1[0] ^ (int)(buff[0] - '0');
            encText[1] = k1[1] ^ (int)(buff[1] - '0');
            encText[2] = k1[2] ^ (int)(buff[2] - '0');
            encText[3] = k1[3] ^ (int)(buff[3] - '0');
            encText[4] = k1[4] ^ (int)(buff[4] - '0');

            //writing the encrypted text to cipherText.txt file and printing to console
            //calculating the total number of bits and changed number of bits
            printf("Encrypted Character: ");
            for (int p = 0; p < 5; p++)
            {
                fprintf(enc, "%i", encText[p]);
                printf("%i", encText[p]);

                if (encText[p] != (int)(buff[0] - '0'))
                {
                    totalBits += 1;
                    changedBits += 1;
                }
                else
                {
                    totalBits += 1;
                }
            }
            fprintf(enc, " ");
            printf("\n");
        }
    }

    //calculating the percentage of changed bits and printing to console
    float changedPercentage = (changedBits / totalBits) * 100;
    printf("Total bits: %g\n", totalBits);
    printf("Changed bits: %g\n", changedBits);
    printf("Changed percentage: %g", changedPercentage);

    fclose(fp);
    fclose(enc);
    fclose(keyStr);
}

//plain text
/*The development of Egyptian myth is difficult to trace. Egyptologists must make educated guesses about its earliest phases, based on written sources that appeared much later. One obvious influence on myth is the Egyptians' natural surroundings. Each day the sun rose and set, bringing light to the land and regulating human activity; each year the Nile flooded, renewing the fertility of the soil and allowing the highly productive farming that sustained Egyptian civilization. Thus the Egyptians saw water and the sun as symbols of life and thought of time as a series of natural cycles. This orderly pattern was at constant risk of disruption: unusually low floods resulted in famine, and high floods destroyed crops and buildings. The hospitable Nile valley was surrounded by harsh desert, populated by peoples the Egyptians regarded as uncivilized enemies of order. For these reasons, the Egyptians saw their land as an isolated place of stability, or maat, surrounded and endangered by chaos. These themes—order, chaos, and renewal—appear repeatedly in Egyptian religious thought. 
Another possible source for mythology is ritual. Many rituals make reference to myths and are sometimes based directly on them. But it is difficult to determine whether a culture's myths developed before rituals or vice versa. Questions about this relationship between myth and ritual have spawned much discussion among Egyptologists and scholars of comparative religion in general. In ancient Egypt, the earliest evidence of religious practices predates written myths. Rituals early in Egyptian history included only a few motifs from myth. For these reasons, some scholars have argued that, in Egypt, rituals emerged before myths. But because the early evidence is so sparse, the question may never be resolved for certain. 
In private rituals, which are often called "magical", the myth and the ritual are particularly closely tied. Many of the myth-like stories that appear in the rituals' texts are not found in other sources. Even the widespread motif of the goddess Isis rescuing her poisoned son Horus appears only in this type of text. The Egyptologist David Frankfurter argues that these rituals adapt basic mythic traditions to fit the specific ritual, creating elaborate new stories (called historiolas) based on myth. In contrast, J. F. Borghouts says of magical texts that there is "not a shred of evidence that a specific kind of 'unorthodox' mythology was coined... for this genre." 
Much of Egyptian mythology consists of origin myths, explaining the beginnings of various elements of the world, including human institutions and natural phenomena. Kingship arises among the gods at the beginning of time and later passed to the human pharaohs; warfare originates when humans begin fighting each other after the sun god's withdrawal into the sky. Myths also describe the supposed beginnings of less fundamental traditions. In a minor mythic episode, Horus becomes angry with his mother Isis and cuts off her head. Isis replaces her lost head with that of a cow. This event explains why Isis was sometimes depicted with the horns of a cow as part of her headdress. 
Some myths may have been inspired by historical events. The unification of Egypt under the pharaohs, at the end of the Predynastic Period around 3100 BC, made the king the focus of Egyptian religion, and thus the ideology of kingship became an important part of mythology. In the wake of unification, gods that were once local patron deities gained national importance, forming new relationships that linked the local deities into a unified national tradition. Geraldine Pinch suggests that early myths may have formed from these relationships. Egyptian sources link the mythical strife between the gods Horus and Set with a conflict between the regions of Upper and Lower Egypt, which may have happened in the late Predynastic era or in the Early Dynastic Period. 
After these early times, most changes to mythology developed and adapted preexisting concepts rather than creating new ones, although there were exceptions. Many scholars have suggested that the myth of the sun god withdrawing into the sky, leaving humans to fight among themselves, was inspired by the breakdown of royal authority and national unity at the end of the Old Kingdom (c. 2686 BC – 2181 BC). In the New Kingdom (c. 1550–1070 BC), minor myths developed around deities like Yam and Anat who had been adopted from Canaanite religion. In contrast, during the Greek and Roman eras (332 BC–641 AD), Greco-Roman culture had little influence on Egyptian mythology

Like myths in many other cultures, Egyptian myths serve to justify human traditions and to address fundamental questions about the world, such as the nature of disorder and the ultimate fate of the universe. The Egyptians explained these profound issues through statements about the gods. 
Egyptian deities represent natural phenomena, from physical objects like the earth or the sun to abstract forces like knowledge and creativity. The actions and interactions of the gods, the Egyptians believed, govern the behavior of all of these forces and elements for the most part, the Egyptians did not describe these mysterious processes in explicit theological writings. Instead, the relationships and interactions of the gods illustrated such processes implicitly. 
Most of Egypt's gods, including many of the major ones, do not have significant roles in any mythic narratives, although their nature and relationships with other deities are often established in lists or bare statements without narration. For the gods who are deeply involved in narratives, mythic events are very important expressions of their roles in the cosmos. Therefore, if only narratives are myths, mythology is a major element in Egyptian religious understanding, but not as essential as it is in many other cultures 

The sky depicted as a cow goddess supported by other deities. This image combines several coexisting visions of the sky: as a roof, as the surface of a sea, as a cow, and as a goddess in human form. 
The true realm of the gods is mysterious and inaccessible to humans. Mythological stories use symbolism to make the events in this realm comprehensible. Not every detail of a mythic account has symbolic significance. Some images and incidents, even in religious texts, are meant simply as visual or dramatic embellishments of broader, more meaningful myths
*/
