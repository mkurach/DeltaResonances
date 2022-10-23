#include "TString.h"
#include <iostream>

const TString TLATEXSYMBOLS[]={"#club", "#voidn", "#leq", "#approx", "#in", "#supset", "#cap", "#ocopyright", "#trademark", "#times", "#bullet", "#voidb", "#doublequote", "#lbar", "#arcbottom", "#downarrow", "#leftrightarrow", "#Downarrow",
                     "#Leftrightarrow", "#void8", "#hbar", "#diamond", "#aleph", "#geq", "#neq", "#notin", "#subseteq", "#cup", "#copyright", "#void3", "#divide", "#circ", "#infty", "#angle", "#cbar", "#arctop",
                     "#leftarrow", "#otimes", "#Leftarrow", "#prod", "#Box", "#parallel", "#heart", "#Jgothic", "#LT", "#equiv", "#subset", "#supseteq", "#wedge", "#oright", "#AA", "#pm", "#mp", "#3dots",
                     "#nabla", "#downleftarrow", "#topbar", "#arcbar", "#uparrow", "#oplus", "#Uparrow", "#sum", "#perp", "#forall", "#spade", "#Rgothic", "#GT", "#propto", "#notsubset", "#oslash", "#vee", "#void1",
                     "#aa", "#/", "#backslash", "#upoint", "#partial", "#corner", "#ltbar", "#bottombar", "#rightarrow", "#surd", "#Rightarrow", "#int", "#odot", "#exists", "#plus", "#minus", "#sqrt", "#frac"};

const TString TLATEXGREEK[]={"#alpha", "#beta", "#gamma", "#delta", "#epsilon", "#zeta" "#eta", "#theta", "#iota", "#kappa", "#lambda", "#mu", "#nu", "#xi", "#omicron", "#pi", "#rho", "#sigma", "#tau", "#upsilon", "#phi", "#chi", "#psi",
                     "#omega", "#Alpha", "#Beta", "#Gamma", "#Delta", "#Epsilon", "#Zeta", "#Eta", "#Theta", "#Iota", "#Kappa", "#Lambda", "#Mu", "#Nu", "#Xi", "#Omicron", "#Pi", "#Rho", "#Sigma", "#Tau", "#Upsilon", "#Phi", "#Chi",
                     "#Psi", "#Omega", "#varepsilon", "#vartheta", "#varsigma", "#varUpsilon", "#varphi", "#varomega"};

const TString TLATEXBRACKETS1[]={"#[]","#{}","#||","#()"};
const TString TLATEXBRACKETS2[]={"#left[","#right]","#left{","#right}","#left|","#right|","#left(","#right)"};

const TString TLATEXACCENTS[]={"#hat","#check","#acute","#grave","#dot","#ddot","#tilde","#slash","#bar","#vec"};

const TString TLATEXOTHERS[]={"{","}","_","^"};


int getTruelength(TString word){
   TString wordBackup=word;

   int nSymbols = sizeof(TLATEXSYMBOLS)/sizeof(*TLATEXSYMBOLS);
   int nGreek = sizeof(TLATEXGREEK)/sizeof(*TLATEXGREEK);
   int nBrackets1 = sizeof(TLATEXBRACKETS1)/sizeof(*TLATEXBRACKETS1);
   int nBrackets2 = sizeof(TLATEXBRACKETS2)/sizeof(*TLATEXBRACKETS2);
   int nAccents = sizeof(TLATEXACCENTS)/sizeof(*TLATEXACCENTS);
   int nOthers = sizeof(TLATEXOTHERS)/sizeof(*TLATEXOTHERS);
   int index=-1000; //some off-limits value

   //loop over symbols
   for(int i=0; i<nSymbols; i++){
      while(index!=-1){
         index = wordBackup.Index(TLATEXSYMBOLS[i]);
         if(index!=-1) wordBackup.Replace(index,TLATEXSYMBOLS[i].Length(),"~"); //if we found something -> replace to tylda (becouse why not, we need to make it single character anyway)
      }
      index=-1000;
   }
   //loop over greek letters
   for(int i=0; i<nGreek; i++){
      while(index!=-1){
         index = wordBackup.Index(TLATEXGREEK[i]);
         if(index!=-1) wordBackup.Replace(index,TLATEXGREEK[i].Length(),"~");
      }
      index=-1000;
   }
   //loop over brackets, defined at front
   for(int i=0; i<nBrackets1; i++){
      while(index!=-1){
         index = wordBackup.Index(TLATEXBRACKETS1[i]);
         if(index!=-1) wordBackup.Replace(index,TLATEXBRACKETS1[i].Length(),""); //if we found something -> remove it completely, since it doesn't produce any actual lenghts
      }
      index=-1000;
   }
   //loop over brackets
   for(int i=0; i<nBrackets2; i++){
      while(index!=-1){
         index = wordBackup.Index(TLATEXBRACKETS2[i]);
         if(index!=-1) wordBackup.Replace(index,TLATEXBRACKETS2[i].Length(),"~");
      }
      index=-1000;
   }
   //loop over accents
   for(int i=0; i<nAccents; i++){
      while(index!=-1){
         index = wordBackup.Index(TLATEXACCENTS[i]);
         if(index!=-1) wordBackup.Replace(index,TLATEXACCENTS[i].Length(),"");
      }
      index=-1000;
   }
   //loop over the rest of this garbage
   for(int i=0; i<nOthers; i++){
      while(index!=-1){
         index = wordBackup.Index(TLATEXOTHERS[i]);
         if(index!=-1) wordBackup.Replace(index,TLATEXOTHERS[i].Length(),"");
      }
      index=-1000;
   }
   return wordBackup.Length();
}