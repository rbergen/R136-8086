#include "r136.h"

void ShowDirString(char *connect);
void ShowItems(Progdata &progdata);
void HellehondStatus(Progdata &progdata);
void RodeTrolStatus(Progdata &progdata);
void PlantStatus(Progdata &progdata);
void GnoeStatus(Progdata &progdata);
void DraakStatus(Progdata &progdata);
void GezwelStatus(Progdata &progdata);
void DeurStatus(Progdata &progdata);
void StemmenStatus(Progdata &progdata);
void BarbecueStatus(Progdata &progdata);
void BoomStatus(Progdata &progdata);
void DiamantStatus(Progdata &progdata);
void ComputerStatus(Progdata &progdata);
void DrakeKopStatus(Progdata &progdata);
bool LavaStatus(Progdata &progdata);
void PapierStatus(Progdata &progdata);

void RoomStatus(Progdata &progdata)
{
	cprintf("Je bevindt je %s.\r\n", progdata.rooms[progdata.status.curroom].name);

	if (progdata.status.curroom != 61
   	&& progdata.status.curroom != 31
      && progdata.status.curroom >= 20
      && !progdata.status.lamp)
	{
   	cputs("Het is stekedonker en je ziet geen hand voor ogen.\r\n");
   }
	else
	{
		if (progdata.rooms[progdata.status.curroom].descript)
			cprintf("%s\r\n", progdata.rooms[progdata.status.curroom].descript);
		ShowItems(progdata);
	}

	ShowDirString(progdata.rooms[progdata.status.curroom].connect);
	cputs("\r\n");
}

void ShowDirString(char *connect)
{
	int count = 0;
	int i;

	for (i = 0; i < 6; i++)
		if (connect[i] != NO_ROOM)
			count++;

	if (!count)
		return;

	cputs("Je kunt naar ");

	for (i = 0; i < 6; i++)
		if (connect[i] != NO_ROOM)
		{
			switch(i)
			{
			case EAST:
				cputs("het oosten");
				break;
			case WEST:
				cputs("het westen");
				break;
			case NORTH:
				cputs("het noorden");
				break;
			case SOUTH:
				cputs("het zuiden");
				break;
			case UP:
				cputs("boven");
				break;
			case DOWN:
				cputs("beneden");
				break;
			}
			switch(--count)
			{
			case 0:
				break;
			case 1:
				cputs(" en ");
				break;
			default:
				cputs(", ");
				break;
			}
		}

	cputs(".\r\n");
}

void ShowItems(Progdata &progdata)
{
	int count = 0;
	int i;

	for (i = 0; i < 25; i++)
		if (progdata.items[i].room == progdata.status.curroom)
			count++;

	if (count)
	{
		cprintf("Hier lig%s ", count > 1 ? "gen" : "t");

		for (i = 0; i < 25; i++)
			if (progdata.items[i].room == progdata.status.curroom)
			{
				if (wherex() > 55)
					cputs("\r\n");
				cputs(progdata.items[i].name);

				switch(--count)
				{
				case 0:
					break;
				case 1:
					cputs(" en ");
					break;
				default:
					cputs(", ");
					break;
				}
			}

		cputs(".\r\n");
	}
}


bool BeastStatus(Progdata &progdata)
{
	int beastfound = -1;
	int i;

	for (i = 0; i < 21 && beastfound == -1; i++)
		if (progdata.living[i].room == progdata.status.curroom)
			beastfound = i;

	switch (beastfound)
	{
	case HELLEHOND:
		HellehondStatus(progdata);
		break;
	case RODETROL:
		RodeTrolStatus(progdata);
		break;
	case PLANT:
		PlantStatus(progdata);
		break;
	case GNOE:
		GnoeStatus(progdata);
		break;
	case DRAAK:
		DraakStatus(progdata);
		break;
	case GEZWEL:
		GezwelStatus(progdata);
		break;
	case DEUR:
		DeurStatus(progdata);
		break;
	case STEMMEN:
		StemmenStatus(progdata);
		break;
	case BARBECUE:
		BarbecueStatus(progdata);
		break;
	case BOOM:
		BoomStatus(progdata);
		break;
	case DIAMANT:
		DiamantStatus(progdata);
		break;
	case COMPUTER:
		ComputerStatus(progdata);
		break;
	case DRAKEKOP:
		DrakeKopStatus(progdata);
		break;
	case LAVA:
		return LavaStatus(progdata);
	case VACUUM:
		cputs("Doordat er in deze grot geen lucht is, klappen allebei je longen dicht. Een\r\n"
      		"verschrikkelijke pijn kraakt als een bliksem door je lijf. Je valt naar achte-\r\n"
				"ren de grot uit, en daar val je even flauw.\r\n\r\n");

		progdata.status.lifepoints -= 4; //   Levenswond
		progdata.status.curroom = 76; //   Grot terug
		return false;
	case PAPIER:
		PapierStatus(progdata);
		break;
	case NOORDMOERAS:
	case MIDDENMOERAS:
	case ZUIDMOERAS:
		cputs("Met de eerste stap die je in het moeras zet, voel je dat je geen vaste grond\r\n"
				"onder de voeten hebt. Ondanks je wilde pogingen boven te blijven zak je\r\n"
				"langzaam het moeras in. Als je tot je nek in de pruttelende, modderige massa\r\n"
				"zit houd je je adem in en doe je je ogen dicht. Je blijft zakken in de smurrie,\r\n"
				"en na enige tijd verlies je je bewustzijn.\r\n"
				"Als je weer bijkomt merk je dat je op een harde ondergrond ligt... in een grot.\r\n\r\n");

		switch (progdata.status.curroom)
		{
		case 3:
			progdata.status.curroom = 51;
			break;
		case 8:
			progdata.status.curroom = 30;
			break;
		case 18:
			progdata.status.curroom = 47;
			break;
		}
		return false;
	case MISTGROT:
		cputs("In deze grot hangt een vreemde, dichte mist, waardoor je geen hand voor ogen\r\n"
            "ziet. Je verliest je orčentatiegevoel en stommelt paniekerig door de grot, op\r\n"
				"zoek naar een uitgang.\r\n"
				"Net als je begint te denken dat je nooit een uitgang uit deze grot zult vinden,\r\n"
				"struikel je voorover een andere grot in.\r\n\r\n");

		switch(random(3))
		{
		case 0:
			progdata.status.curroom = 36;
			break;
		case 1:
			progdata.status.curroom = 32;
			break;
		case 2:
			progdata.status.curroom = 38;
			break;
		}
		return false;
	case TELEPORT:
		cputs("Als je deze grot binnenloopt zie je een aantal pulserende lampen aan het\r\n"
				"plafond en tegen een van de wanden een enorm apparaat met een aantal\r\n"
				"bedieningspanelen en beeldschermen.\r\n"
				"Terwijl je ernaartoe loopt om het beter te bekijken struikel je over een pedaal\r\n"
				"in de grond, waarna een sirene begint te loeien. Van de schrik blijf je liggen,\r\n"
				"en je ziet dat de lampen aan het plafond feller gaan branden en er grote\r\n"
				"hoeveelheden data over de beeldschermen flitsen. Even later zie je een\r\n"
				"oogverblindende flits en voel je je even gewichtloos.\r\n"
				"Als je weer kunt zien, merk je dat de lampen en de machine zijn verdwenen.\r\n"
				"Sterker nog, je ligt buiten...\r\n\r\n");

		progdata.status.curroom = 1;
		return false;
	}
	return true;
}

void HellehondStatus(Progdata &progdata)
{
	switch (progdata.living[HELLEHOND].status)
	{
	case 0:
		cputs("Er staat hier een reusachtige hellehond die je de weg verspert. Zijn scherpe\r\n"
				"tanden steken duidelijk af, en het rode kwijl druipt langzaam uit zijn bek.\r\n"
				"Hij kijkt je dreigend aan met zijn bloeddoorlopen ogen, en uit zijn keel\r\n"
				"klinkt een diep gegrom.\r\n\r\n");

		progdata.living[HELLEHOND].status = 1;
		break;
	case 1:
		cputs("De hellehond zet zich af tegen de grond, en hij spring boven op je lijf. Zijn\r\n"
				"nagels boren zich in je vlees, en op een gegeven moment bijt hij je hard in je\r\n"
				"schouder. Je botten kraken en een scheut van pijn trekt door je zenuwen. De\r\n"
				"hond laat je los, en hij kijkt je grommend aan.\r\n\r\n");

		progdata.status.lifepoints--; //  Wond
		progdata.living[HELLEHOND].status = 2;
		break;
	case 2:
		cputs("De honger van de hellehond is nog niet gestild. Een diep gegrom komt uit zijn\r\n"
				"keel, en hij staat klaar om opnieuw aan te vallen.\r\n\r\n");

		progdata.living[HELLEHOND].status = random(2) + 1;
		break;
	case 3:
		cputs("Door de wonden aangericht met je zwaard sterft de hevig bloedende hellehond. Je\r\n"
				"deelt nog een slag uit, en een stuk vlees van de hond laat los.\r\n\r\n");

		progdata.items[HONDVLEES].room = progdata.status.curroom;
		progdata.living[HELLEHOND].status = 4;
		break;
	case 4:
		cputs("De dode hellehond ligt in een bad van dampend bloed.\r\n\r\n");
		break;
	}
}

void RodeTrolStatus(Progdata &progdata)
{
	switch (progdata.living[RODETROL].status)
	{
	case 0:
      cputs("Je hebt de rust van de rode trol verstoord. Hij kijkt zwaar ge" E_TREMA "rgerd.\r\n\r\n");

		progdata.living[RODETROL].status = 1;
		break;
	case 1:
		cputs("Nu is de trol pas echt goed wakker. Hij pakt zijn zweep en komt dreigend op je\r\n"
				"af.\r\n\r\n");

		progdata.living[RODETROL].status = 2;
		break;
	case 2:
		cputs("De trol deelt je een harde klap uit met z'n zweep. Je voelt de brandende pijn\r\n"
				"tot je botten doordringen.\r\n\r\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[RODETROL].status = 3;
		break;
	case 3:
		cputs("Het schuim loopt uit de trol z'n bek. Hij heft opnieuw zijn zweep.\r\n\r\n");

		progdata.living[RODETROL].status = random(2) + 2;
		break;
	case 4:
		cputs("Opgewonden grijpt de trol het boekje. Hij bladert het door, en wordt roder en\r\n"
				"roder. Op een gegeven moment klinkt een geborrel op uit het wezen, en met een\r\n"
				"klap springt hij uit elkaar. Van de rotswanden druipen de resten van de trol\r\n"
				"langzaam naar beneden.\r\n"
				"Opeens zie je iets glinsteren.\r\n\r\n");

		progdata.items[ROODKRISTAL].room = progdata.status.curroom;
		progdata.living[RODETROL].status = 5;
		break;
	case 5:
		cputs("Overal in de grot liggen stukken van de verscheurde trol verspreid. Het slijm\r\n"
      		"zuigt aan je schoenen, en een vieze stank dringt in je neus.\r\n\r\n");

		break;
	}
}

void PlantStatus(Progdata &progdata)
{
	switch (progdata.living[PLANT].status)
	{
	case 0:
		cputs("In deze grot leeft een vleesetende plant. Zijn dikke groene stengel loopt uit\r\n"
				"in een afschrikwekkende kop, met afzichtelijke tanden. Hij heeft je gezien en\r\n"
				"beweegt zijn opengesperde bek in je richting. Voordat je een stap hebt kunnen\r\n"
				"zetten zit je verstrengd in het monster, en zet de plant zijn tanden in je\r\n"
				"nek.\r\n\r\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[PLANT].status = random(2) + 1;
		break;
	case 1:
		cputs("De plant likt met zijn kleine schurfterige tongetje je bloed van zijn bek.\r\n"
				"Met zijn groene oogjes kijkt hij je weer aan, en hij maakt aanstalten zijn\r\n"
				"tanden opnieuw in je nek te zetten.\r\n\r\n");

		progdata.living[PLANT].status = 2;
		break;
	case 2:
		cputs("Opnieuw omsluit de bek van de plant je hals. Een warme stroom bloed loopt via\r\n"
				"je rug naar beneden, en de pijn is nu ondraaglijk. Na een tijdje laat de plant\r\n"
				"je weer los.\r\n\r\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[PLANT].status = random(2) + 1;
		break;
	case 3:
		cputs("De resten van wat eerst een vleesetende plant was liggen nu op de grond van\r\n"
				"de grot. Zijn bek ligt opengesperd, en zijn ogen rollen bijna uit zijn oogkas-\r\n"
				"sen. Uit zijn stengel druipt langzaam het bloed van zijn slachtoffers.\r\n"
				"Op de plek waar vroeger zijn beschimmelde wortels waren zit nu een opening.\r\n\r\n");

		progdata.rooms[25].connect[NORTH] = 20; //	Maak verbinding met slijmgrot
		progdata.living[PLANT].status = 4;
		break;
	case 4:
		cputs("De vleesetende plant is niet veel meer dan een berg stinkend tuinafval.\r\n\r\n");

		break;
	}
}

void GnoeStatus(Progdata &progdata)
{
	switch (progdata.living[GNOE].status)
	{
	case 0:
		cputs("Er staat hier een grote behaarde gnoe die je met twee geniepige oogjes aan-\r\n"
				"kijkt. Tussen de haren van zijn vacht bevinden zich allerlei kleine kruipende\r\n"
				"beestjes, die je nog nooit eerder gezien hebt. Het beest verspreidt een\r\n"
				"afschuwelijke lucht. Kweilend en zwaar snuivend komt hij langzaam naar je toe.\r\n\r\n");

		progdata.living[GNOE].status = 1;
		break;
	case 1:
		cputs("De gnoe neemt een sprong, en stoot met zijn grote kop hard in je maag. Je\r\n"
				"hebt het gevoel alsof je longen uit je lijf worden geperst. Versuft sta je\r\n"
				"weer op.\r\n\r\n");

		progdata.status.lifepoints--; //   Wond
		break;
	case 2:
      cputs("De gnoe ziet het vlees, snuffelt er aan, en slokt het in " E_GRAVE E_GRAVE "n hap naar binnen.\r\n"
				"Je ziet hem langzaam opzwellen en zijn hersens komen door zijn oogkassen naar\r\n"
				"buiten. Hij zakt in elkaar en blijft roerloos liggen.\r\n\r\n");

		progdata.living[GNOE].status = 3;
		break;
	case 3:
		cputs("Het bultachtige lichaam van de gnoe ligt op de grond en de hersens liggen er\r\n"
				"als een papje naast.\r\n\r\n");

		break;
	}
}

void DraakStatus(Progdata &progdata)
{
	switch (progdata.living[DRAAK].status)
	{
	case 0:
		cputs("In deze grot bevindt zich een grote draak. Hij heeft meerdere koppen, die je\r\n"
				"allemaal bespieden met gele oogjes. Zijn hele huid is bedekt met schimmel, en\r\n"
				"uit zijn bekken hangen lange, bruine tongen, waar een bijtend zuur af drup-\r\n"
				"pelt. Opeens komt uit een van de bekken een rommelend geluid. Met moeite\r\n"
				"versta je \"Ben jij een koekie?\".\r\n\r\n");

		progdata.living[DRAAK].status = 1;
		break;
	case 1:
		cputs("De koppen van de draak bewegen nu agressiever heen en weer en beginnen hevig\r\n"
				"te snuiven.\r\n"
				"De lucht uit de drakekoppen ruikt afgrijselijk, en je slaat achterover van\r\n"
				"walging. Een van de bekken spert zich wijd open, en harder dan eerst klinkt\r\n"
				"\"BEN JIJ EEN KOEKIE?!?\".\r\n\r\n");

		progdata.living[DRAAK].status = 2;
		break;
	case 2:
		cputs("De draak heft langzaam een van zijn gore poten op, en geeft opeens een ontzet-\r\n"
				"tende harde klap. Er kraakt iets in je hoofd, en een duizeling maakt zich van\r\n"
				"je meester. Hij maakt aanstalten je nog een klap te verkopen.\r\n\r\n");

		progdata.status.lifepoints--; //   Wond
		break;
	case 3:
		cputs("De draak grijpt het koekje, en steekt hem gelijk in een van zijn grote bekken.\r\n"
				"Langzaam begint hij te wankelen, en met een doffe dreun klapt hij op de grond.\r\n"
				"Uit de bek waar juist het koekje in verdween druipt wat kwijl. De draak\r\n"
				"slaapt.\r\n\r\n");

		progdata.living[DRAAK].status = 4;
		break;
	case 4:
		cputs("De draak slaapt onrustig. Soms beweegt een van zijn koppen iets, en uit zijn\r\n"
				"lijf klinkt een diep gegrom.\r\n\r\n");

		break;
	case 5:
		cputs("Voorzichtig zet je de draak de slaapmuts op. De vrolijke kleuren van de muts\r\n"
				"steken af tegen de beschimmelde huid, en de muts zakt iets scheef. Op een ge-\r\n"
				"geven moment valt er iets, en het klettert tegen de harde rotsvloer.\r\n\r\n");

		progdata.items[GASPATROON].room = progdata.status.curroom;
		progdata.living[DRAAK].status = 6;
		break;
	case 6:
		cputs("De draak slaapt rustig.\r\n\r\n");

		break;
	}
}

void GezwelStatus(Progdata &progdata)
{
	switch (progdata.living[GEZWEL].status)
	{
	case 0:
		cputs("Er staat hier een wezen dat nog het meest lijkt op een gezwel. Het kijkt je\r\n"
				"aan met 2 gluiperige ogen, op zijn huid zitten schurftvlekken, en op zijn\r\n"
				"mondhoeken groeien algen. Met zijn lange, glibberige tentakels houdt het zich\r\n"
				"vast aan alle wanden van de grot en verspert zo je weg.\r\n\r\n");

		progdata.living[GEZWEL].status = 1;
		break;
	case 1:
		cputs("Het gezwel zit nog steeds aan de grotwanden vastgezogen, en het trilt licht.\r\n\r\n");

		break;
	case 2:
		if (progdata.items[GASMASKER].room == -2)
		// gasmasker op
		{
			cputs("Als je op de hendel drukt, zie je een bruingrijs gas uit het patroon spuiten.\r\n"
					"Het gezwel begint langzaam steeds heftiger te trillen, en langzaam komen\r\n"
					"overal scheuren in zijn schurfterige huid. Zijn tentakels komen langzaam met\r\n"
					"een luid slurpend geluid los van de rotswanden, en hij zakt helemaal in el-\r\n"
					"kaar.\r\n\r\n");
		}
		else
		// geen masker... oeps!
		{
			cputs("Je kunt nog zien dat het gezwel langzaam steeds heftiger begint te trillen,\r\n"
					"voordat je zelf een kloppende hoofdpijn krijgt en onderuit gaat. Je hebt niets\r\n"
					"om je tegen het gas te beschermen, en je valt flauw. Na een tijdje kom je weer\r\n"
					"bij.\r\n\r\n");

			progdata.status.lifepoints -= 4; //    Grote wond
		}
		progdata.rooms[75].connect[NORTH] = 70;
		progdata.living[GEZWEL].status = 4;
		break;
	case 4:
		cputs("Op het gescheurde lichaam van het gezwel zitten allemaal schimmels. Uit zijn\r\n"
				"maag kruipen pissebedden en oorkruipers. Er verspreidt zich een sterke rot-\r\n"
				"lucht, en er ontstaat langzaam een klein slijmplasje.\r\n\r\n");

		break;
	}
}

void DeurStatus(Progdata &progdata)
{
	switch (progdata.living[DEUR].status)
	{
	case 0:
		cputs("In het noorden zit een grote, vastgeroeste deur. Hij is met blote handen niet\r\n"
      		"meer open te krijgen.\r\n\r\n");

		break;
	case 1:
		cputs("Je zet 1 eind van het bot onder de deur, en op het andere begin je te duwen.\r\n"
				"Na lang wrikken begint de deur hevig te kraken en te piepen, en vormt zich een\r\n"
				"kier. Je geeft nog een duw, en langzaam draait de deur open.\r\n\r\n");

		progdata.rooms[45].connect[NORTH] = 40;
		progdata.living[DEUR].status = 2;
		break;
	case 2:
		cputs("De deur is nu open, en geeft toegang tot een grot.\r\n\r\n");

		break;
	}
}

void StemmenStatus(Progdata &progdata)
{
	switch (progdata.living[STEMMEN].status)
	{
	case 0:
		cputs("Uit het niets hoor je opeens een paar stemmen. Met moeite kun je ze verstaan:\r\n"
				"\"Wat schreeuwt is in z'n hart nog een kind\".\r\n"
				"Dan is het weer stil.\r\n\r\n");

		progdata.living[STEMMEN].status = 1;
		break;
	case 1:
		cputs("Vanuit de verte hoor je zachte, lachende stemmetjes.\r\n\r\n");

		break;
	}
}

void BarbecueStatus(Progdata &progdata)
{
	switch (progdata.living[BARBECUE].status)
	{
	case 0:
		cputs("Op deze open plek staat een barbecue gezellig te branden.\r\n\r\n");

		break;
	case 1:
		cputs("Als je de hasj op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt\r\n"
				"er niets.\r\n\r\n");

		progdata.living[BARBECUE].status = 3;
		break;
	case 2:
		cputs("Als je het vlees op de barbecue gooit verschiet de vlam van kleur. Verder\r\n"
				"gebeurt er niets.\r\n\r\n");

		progdata.living[BARBECUE].status = 3;
		break;
	case 3:
		cputs("De barbecue brandt nog steeds, alleen iets onrustiger dan eerst.\r\n\r\n");

		break;
	case 4:
      cputs("Een grote rookontwikkeling treedt op wanneer het tweede ingrediČnt in de\r\n"
				"barbecue belandt.\r\n"
            "Knetterend smelten de 2 ingredi" E_TREMA "nten om tot een koekje.\r\n\r\n");

		progdata.items[KOEKJE].room = progdata.status.curroom;
		progdata.living[BARBECUE].status = 0;
		break;
	}
}

void ApplySimmeringForest(Progdata &progdata)
{
   static char *smeulendbos = "Om je heen zie je de smeulende resten van wat eens bos was.";

	for (int i = 0; i < 20; i += 5)
		for (int j = 0; j < 2; j++)
			if (i + j != 6)
				progdata.rooms[i + j].descript = smeulendbos;
	progdata.rooms[2].descript = smeulendbos;
	progdata.rooms[4].descript = smeulendbos;
	progdata.rooms[7].descript = smeulendbos;
}

void BoomStatus(Progdata &progdata)
{
	switch (progdata.living[BOOM].status)
	{
	case 0:
		cputs("In een kleine open plek staat een grote, kurkdroge, dode boom. Op de stam zit\r\n"
				"een bordje met daarop de tekst \"Roken en open vuur verboden\".\r\n\r\n");

		break;
	case 1:
		cputs("Uit de pijp van de vlammenwerper spuit een enorme vlam. De boom begint langzaam\r\n"
				"te branden, en weldra staat hij in lichterlaaie. De vlammen slaan om zich heen,\r\n"
				"en het hele bos begint mee te branden. Je bent omringd door een enorme vuurzee,\r\n"
				"en de hitte is enorm.\r\n\r\n");

		if (progdata.items[HITTEPAK].room != OWNED)
		{
			cputs("Je hebt niets om je te beschermen tegen de hitte, en je loopt flinke brandwon-\r\n"
					"den op.\r\n\r\n");

			progdata.status.lifepoints -= 4; //   Levenswond
		}

      ApplySimmeringForest(progdata);

		progdata.items[GROENKRISTAL].room = 4;
		progdata.living[DIAMANT].status = 1;
		progdata.living[BOOM].status = 2;
		break;
	case 2:
		cputs("Uit de grond steken nog een paar wortels, en er naast ligt een verkoold stuk\r\n"
				"bord met daarop \"R   n e  op n v u  ver  d n\".\r\n\r\n");

		break;
	}
}

void DiamantStatus(Progdata &progdata)
{
	switch (progdata.living[DIAMANT].status)
	{
	case 0:
      cputs("Je struikelt over iets. Door de begroečing zie je niet wat het is.\r\n\r\n");

		break;
	}
}

void ComputerStatus(Progdata &progdata)
{
	switch (progdata.living[COMPUTER].status)
	{
	case 0:
		cputs("Er staat een computer van het merk Beull die bestaat bestaat uit een kast met\r\n"
				"een 3.5-inch drive en een monitor. Op de monitor staat: \"Datadisk invoeren\r\n"
				"a.u.b.\".\r\n\r\n");

		progdata.living[COMPUTER].status = 1;
		break;
	case 1:
		cputs("De computer wacht nog steeds.\r\n\r\n");

		break;
	case 2:
		cputs("De drive begint te lezen en na korte tijd verschijnt er informatie op het\r\n"
				"scherm. Er staat: \"In het onderste grottenstelsel moet men een letter-\r\n"
				"route volgen die resulteert in de naam van het te vinden voorwerp.\".\r\n"
				"Na even wordt het scherm zwart.\r\n\r\n");

		progdata.living[COMPUTER].status = 3;
		break;
	case 3:
		cputs("Er valt niets te zien op de monitor en de computer is stil.\r\n\r\n");

		break;
	}
}

void DrakeKopStatus(Progdata &progdata)
{
	switch (progdata.living[DRAKEKOP].status)
	{
	case 0:
		cputs("Er zit in het noorden een zware, dichte deur met daarnaast een drakekop met een\r\n"
				"geopende muil. Op de deur zit een zwaar slot.\r\n\r\n");

		break;
	case 1:
		cputs("Je stopt het kristal in de muil van de drakekop, die daarop dicht- en weer\r\n"
				"opengaat. Het kristal is nu verdwenen, en de ogen van de kop beginnen licht te\r\n"
				"gloeien.\r\n\r\n");

		progdata.living[DRAKEKOP].status = 2;
		break;
	case 2:
		cputs("De ogen van de draak blijven licht gloeien.\r\n\r\n");

		break;
	case 3:
		cputs("Je stopt nog een kristal in de muil. Weer sluit en opent deze, en weer is het\r\n"
				"kristal verdwenen. Het schijnsel uit de ogen wordt nu sterker.\r\n\r\n");

		progdata.living[DRAKEKOP].status = 4;
		break;
	case 4:
		cputs("De ogen van de draak blijven gloeien.\r\n\r\n");

		break;
	case 5:
		cputs("Je legt het laatste kristal in de kop. De muil sluit zich weer, en nu blijft\r\n"
				"hij dicht. De ogen beginnen nu steeds feller te gloeien. Op een gegeven moment\r\n"
				"concentreert de gloed zich tot een erg felle lichtstraal, die langs je schiet\r\n"
				"en wordt weerkaatst in een spiegel vlak achter je. De spiegel reflecteert het\r\n"
				"licht met akelige precisie op het zware slot dat door de enorme hitte verdampt.\r\n"
				"Daarna zwaait de deur langzaam met veel gepiep open.\r\n\r\n");

		progdata.rooms[32].connect[NORTH] = 27;
		progdata.living[DRAKEKOP].status = 6;
		break;
	case 6:
		cputs("De zware deur is nu open en geeft toegang tot een ruimte.\r\n\r\n");

		break;
	}
}

bool LavaStatus(Progdata &progdata)
{
	switch (progdata.living[LAVA].status)
	{
	case 0:
		if (progdata.items[HITTEPAK].room == OWNED)
			cputs("Voor je zie je een krater waarin lava opborrelt. Van het lava komt een dikke\r\n"
					"damp, en een rode gloed verlicht de omtrek. De hitte is enorm, maar het hitte-\r\n"
					"pak beschermt je tegen verbranding.\r\n\r\n");
		else
		{
			cputs("Voor je zie je een krater waarin lava opborrelt. De hitte is zo intens, dat je\r\n"
					"een aantal brandwonden oploopt en naar achteren wordt geblazen.\r\n\r\n");

			progdata.status.curroom = 54; //   Grot terug
			progdata.status.lifepoints -= 4; //   Levenswond
			return false;
		}
		return true;
	case 1:
		cputs("Je gooit de positronenbom met een pisboogje in de lava. Met luid gesis zakt\r\n"
				"de bom langzaam weg naar beneden. De lava begint op een gegeven moment vreemd\r\n"
				"te borrelen en verschiet ineens van rood naar groen. Dan zie je een oogver-\r\n"
				"blindende flits vanuit het lava. Daarna wordt het weer rustiger.\r\n\r\n"
				"Het lijkt erop dat je de wereld hebt behoed voor de totaalvernietiging door\r\n"
				"dit positronenwapen, waarvan de beginselen mede van jouw handen komen. Je mis-\r\n"
				"sie is voltooid, en vermoeid en vol van gemengde gevoelens verlaat je het\r\n"
				"grottenstelsel.\r\n\r\n");

		ForceExit();
	}
	return true;
}

void PapierStatus(Progdata &progdata)
{
	switch (progdata.living[PAPIER].status)
	{
	case 0:
		cputs("Er zit een dicht, houten luik in het plafond. Je kunt er niet bij.\r\n\r\n");

		break;
	case 1:
		cputs("Het luik in het plafond gaat open en er dwarrelt een vel papier naar beneden.\r\n\r\n");

		progdata.items[PAPIERITEM].room = 66;
		progdata.living[PAPIER].status = 2;
		break;
	case 2:
		cputs("Het luik aan het plafond hangt nu open. Er zit een leeg gat.\r\n\r\n");

		break;
	}
}


