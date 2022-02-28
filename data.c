//fichier d'implementation des données constantes

#include "data.h"
#include "fonctions_outils.h"

//table contenant les noms des registres (mnemo et decimaux) en les faisant corespondre à leur index dans la table
const nom_registre table_corres_reg[33] = {
						{.mnemo="$zero",.reg="$0"},
						{.mnemo="$at",.reg="$1"},
						{.mnemo="$v0",.reg="$2"},
						{.mnemo="$v1",.reg="$3"},
						{.mnemo="$a0",.reg="$4"},
						{.mnemo="$a1",.reg="$5"},
						{.mnemo="$a2",.reg="$6"},
						{.mnemo="$a3",.reg="$7"},
						{.mnemo="$t0",.reg="$8"},
						{.mnemo="$t1",.reg="$9"},
						{.mnemo="$t2",.reg="$10"},
						{.mnemo="$t3",.reg="$11"},
						{.mnemo="$t4",.reg="$12"},
						{.mnemo="$t5",.reg="$13"},
						{.mnemo="$t6",.reg="$14"},
						{.mnemo="$t7",.reg="$15"},
						{.mnemo="$s0",.reg="$16"},
						{.mnemo="$s1",.reg="$17"},
						{.mnemo="$s2",.reg="$18"},
						{.mnemo="$s3",.reg="$19"},
						{.mnemo="$s4",.reg="$20"},
						{.mnemo="$s5",.reg="$21"},
						{.mnemo="$s6",.reg="$22"},
						{.mnemo="$s7",.reg="$23"},
						{.mnemo="$t8",.reg="$24"},
						{.mnemo="$t9",.reg="$25"},
						{.mnemo="$k0",.reg="$26"},
						{.mnemo="$k1",.reg="$27"},
						{.mnemo="$gp",.reg="$28"},
						{.mnemo="$sp",.reg="$29"},
						{.mnemo="$fp",.reg="$30"},
						{.mnemo="$ra",.reg="$31"},
						{.mnemo="ERREUR",.reg="ERREUR",}
};

//table contenant les noms des fonctions en les faisant correspondre à leur type
const type_fct table_type_fct[28] = {
						{.nom="ADDI",.type='I'},
						{.nom="ADD",.type='R'},
						{.nom="BEQ",.type='I'},
						{.nom="BGTZ",.type='I'},
						{.nom="BLEZ",.type='I'},
						{.nom="BNE",.type='I'},
						{.nom="AND",.type='R'},
						{.nom="OR",.type='R'},
						{.nom="XOR",.type='R'},
						{.nom="LW",.type='I'},
						{.nom="LUI",.type='I'},
						{.nom="SW",.type='I'},
						{.nom="JAL",.type='J'},
						{.nom="J",.type='J'},
						{.nom="DIV",.type='R'},
						{.nom="JR",.type='R'},
						{.nom="MFHI",.type='R'},
						{.nom="MFLO",.type='R'},
						{.nom="MULT",.type='R'},
						{.nom="NOP",.type='R'},
						{.nom="ROTR",.type='R'},
						{.nom="SLL",.type='R'},
						{.nom="SLT",.type='R'},
						{.nom="SRL",.type='R'},
						{.nom="SUB",.type='R'},
						{.nom="SYSCALL",.type='R'},
						{.nom="EXIT",.type='I'},
						{.nom="ERREUR",.type='X'}
};

//table contenant les noms fonctions de type I en les faisant correspondre à leur opcode et la place de leurs operandes
const patternFctI table_pattern_fct_I[10]={
						{.nom = "ADDI",.opcode = {0,0,1,0,0,0},.place_rs = 2,.place_rt = 1,.place_immediate = 3,.nb_mot_voulu = 4},
						{.nom = "BEQ",.opcode = {0,0,0,1,0,0},.place_rs = 1,.place_rt = 2,.place_immediate = 3,.nb_mot_voulu = 4},
						{.nom = "BGTZ",.opcode = {0,0,0,1,1,1},.place_rs = 1,.place_rt = -1,.place_immediate = 2,.nb_mot_voulu = 3},
						{.nom = "BLEZ",.opcode = {0,0,0,1,1,0},.place_rs = 1,.place_rt = -1,.place_immediate = 2,.nb_mot_voulu = 3},
						{.nom = "BNE",.opcode = {0,0,0,1,0,1},.place_rs = 1,.place_rt = 2,.place_immediate = 3,.nb_mot_voulu = 4},
						{.nom = "LW",.opcode = {1,0,0,0,1,1},.place_rs = 3,.place_rt = 1,.place_immediate = 2,.nb_mot_voulu = 4},
						{.nom = "SW",.opcode = {1,0,1,0,1,1},.place_rs = 3,.place_rt = 1,.place_immediate = 2,.nb_mot_voulu = 4},
						{.nom = "LUI",.opcode = {0,0,1,1,1,1},.place_rs = -1,.place_rt = 1,.place_immediate = 2,.nb_mot_voulu = 3},
						{.nom = "EXIT",.opcode = {0,0,0,0,0,1},.place_rs = -1,.place_rt = -1,.place_immediate = -1,.nb_mot_voulu = 1},
						{.nom = "ERREUR",.opcode = {-1,-1,-1,-1,-1,-1},.place_rs = -1,.place_rt = -1,.place_immediate = -1,.nb_mot_voulu = 0}
};

//table contenant les noms fonctions de type J en les faisant correspondre à leur opcode
const patternFctJ table_pattern_fct_J[3]={
						{.nom = "J",.opcode = {0,0,0,0,1,0}},
						{.nom = "JAL" ,.opcode = {0,0,0,0,1,1}},
						{.nom = "ERREUR" ,.opcode = {-1,-1,-1,-1,-1,-1}}
};

//table contenant les noms fonctions de type R en les faisant correspondre à leur opcode et la place de leurs operandes
const patternFctR table_pattern_fct_R[17]={
						{.nom = "ADD",.opcode = {0,0,0,0,0,0},.function = {1,0,0,0,0,0},.place_rs = 2,.place_rt = 3,.place_rd = 1,.place_sa = -1,.nb_mot_voulu = 4},
						{.nom = "AND",.opcode = {0,0,0,0,0,0},.function = {1,0,0,1,0,0},.place_rs = 2,.place_rt = 3,.place_rd = 1,.place_sa = -1,.nb_mot_voulu = 4},
						{.nom = "DIV",.opcode = {0,0,0,0,0,0},.function = {0,1,1,0,1,0},.place_rs = 1,.place_rt = 2,.place_rd = -1,.place_sa = -1,.nb_mot_voulu = 3},
						{.nom = "JR",.opcode = {0,0,0,0,0,0},.function = {0,0,1,0,0,0},.place_rs = 1,.place_rt = -1,.place_rd = -1,.place_sa = -1,.nb_mot_voulu = 2},
						{.nom = "MFHI",.opcode = {0,0,0,0,0,0},.function = {0,1,0,0,0,0},.place_rs = -1,.place_rt = -1,.place_rd = 1,.place_sa = -1,.nb_mot_voulu = 2},
						{.nom = "MFLO",.opcode = {0,0,0,0,0,0},.function = {0,1,0,0,1,0},.place_rs = -1,.place_rt = -1,.place_rd = 1,.place_sa = -1,.nb_mot_voulu = 2},
						{.nom = "MULT",.opcode = {0,0,0,0,0,0},.function = {0,1,1,0,0,0},.place_rs = 1,.place_rt = 2,.place_rd = -1,.place_sa = -1,.nb_mot_voulu = 3},
						{.nom = "NOP",.opcode = {0,0,0,0,0,0},.function = {0,0,0,0,0,0},.place_rs = -1,.place_rt = -1,.place_rd = -1,.place_sa = -1,.nb_mot_voulu = 1},
						{.nom = "OR",.opcode = {0,0,0,0,0,0},.function = {1,0,0,1,0,1},.place_rs = 2,.place_rt = 3,.place_rd = 1,.place_sa = -1,.nb_mot_voulu = 4},
						{.nom = "ROTR",.opcode = {0,0,0,0,0,0},.function = {0,0,0,0,1,0},.place_rs = 21,.place_rt = 2,.place_rd = 1,.place_sa = 3,.nb_mot_voulu = 4},//ici la place de rs renvois vers le bits special 21 (0 ou 1 selon SRL ou ROTR)
						{.nom = "SLL",.opcode = {0,0,0,0,0,0},.function = {0,0,0,0,0,0},.place_rs = -1,.place_rt = 2,.place_rd = 1,.place_sa = 3,.nb_mot_voulu = 4},
						{.nom = "SLT",.opcode = {0,0,0,0,0,0},.function = {1,0,1,0,1,0},.place_rs = 2,.place_rt = 3,.place_rd = 1,.place_sa = -1,.nb_mot_voulu = 4},
						{.nom = "SRL",.opcode = {0,0,0,0,0,0},.function = {0,0,0,0,1,0},.place_rs = -1,.place_rt = 2,.place_rd = 1,.place_sa = 3,.nb_mot_voulu = 4},//le bit special 21 est à 0, on peut donc remplir rs avec des 0
						{.nom = "SUB",.opcode = {0,0,0,0,0,0},.function = {1,0,0,0,1,0},.place_rs = 2,.place_rt =3 ,.place_rd = 1,.place_sa = -1,.nb_mot_voulu = 4},
						{.nom = "SYSCALL",.opcode = {0,0,0,0,0,0},.function = {0,0,1,1,0,0},.place_rs = -1,.place_rt = -1,.place_rd = -1,.place_sa = -1,.nb_mot_voulu = 1},//SYSCALL requiert que les registres fonctionnent car le code est stocké dans $v0.
						{.nom = "XOR",.opcode = {0,0,0,0,0,0},.function = {1,0,0,1,1,0},.place_rs = 2,.place_rt = 3,.place_rd = 1,.place_sa = -1,.nb_mot_voulu = 4},
						{.nom = "ERREUR",.opcode = {-1,-1,-1,-1,-1,-1},.function = {-1,-1,-1,-1,-1,-1},.place_rs = -1,.place_rt = -1,.place_rd = -1,.place_sa = -1,.nb_mot_voulu = 0}
};
