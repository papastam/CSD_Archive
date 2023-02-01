$(document).ready(function(){

});


//playing:1 is for the red player
//playing:2 is for the yellow player
const game={
	playing:0,
	moves:0,
	grid:[],
	winner:0,
}

game.grid[0]=[0,0,0,0,0,0,0];
game.grid[1]=[0,0,0,0,0,0,0];
game.grid[2]=[0,0,0,0,0,0,0];
game.grid[3]=[0,0,0,0,0,0,0];
game.grid[4]=[0,0,0,0,0,0,0];
game.grid[5]=[0,0,0,0,0,0,0];


function newGame(){
	game.playing=Math.floor((Math.random()*10)%2)+1;

	updatePage();
}

function getPlayerTurn(){return game.playing;}
function isDraw(){if(game.moves<42){return 0;}else{return 1;}}

function blink4(i,j,typeofwin){
	var basepl=game.grid[i][j];
	switch(typeofwin){
		case 1:
	    	//Vertical Win
	    	for(var jind=0;jind<4;jind++){
	    		$("#c"+i+"_"+(j+jind)).addClass("blink");
	    	}
	    	break;
	  	case 2:
	    	//Horizontal Win
	    	for(var iind=0;iind<4;iind++){
	    		$("#c"+(i+iind)+"_"+j).addClass("blink");
	    	}
	    	break;
		case 3:
	    	//Diagonial Win (DOWN)
	    	for(var ind=0;ind<4;ind++){
	    		$("#c"+(i+ind)+"_"+(j+ind)).addClass("blink");
	    	}
	    	break;
	  	case 4:
	    	//Diagonial Win (UP)
	    	for(var ind=0;ind<4;ind++){
	    		$("#c"+(i-ind)+"_"+(j+ind)).addClass("blink");
	    	}
	    	break;
	    case 5:
	    	//Draw
	    	for(var ii=0;ii<6;ii++){
	    		for(var jj=0;jj<7;jj++){
	    			$("#c"+ii+"_"+jj).addClass("blink");
	    		}
	    	}
	    	break;
	  	default:
	    	// code block
	}
}

function verticalWin(i,j){
	if(j>3){return 0;}
	var basepl=game.grid[i][j];
	for(var jind=0;jind<4;jind++){
		console.log("testing for VW on "+i+","+j+"+"+jind);
		if(game.grid[i][j+jind]!=basepl){
			console.log("dif pl");
			return 0;
		}else if(jind==3){
			return basepl;
		}
	}
	return 0;
}

function horizontalWin(i,j){
	if(i>2){return 0;}
	var basepl=game.grid[i][j];
	for(var iind=0;iind<4;iind++){
		console.log("testing for HW on "+i+"+"+iind+","+j);
		if(game.grid[i+iind][j]!=basepl){
			console.log("dif pl");
			return 0;
		}else if(iind==3){
			return basepl;
		}
	}
	return 0;
}

function diagonialWin1(i,j){
	if(i>2 || j>3){return 0;}
	var basepl=game.grid[i][j];
	for(var ind=0;ind<4;ind++){
		console.log("testing for DW1 on "+i+"+"+ind+","+j+"+"+ind);
		if(game.grid[i+ind][j+ind]!=basepl){
			console.log("dif pl");
			return 0;
		}else if(ind==3){
			return basepl;
		}
	}
	return 0;
}

function diagonialWin2(i,j){
	if(i<3 || j>3){return 0;}
	var basepl=game.grid[i][j];
	for(var ind=0;ind<4;ind++){
		console.log("testing for DW2 on "+i+"-"+ind+","+j+"+"+ind);
		if(game.grid[i-ind][j+ind]!=basepl){
			console.log("dif pl");
			return 0;
		}else if(ind==3){
			return basepl;
		}
	}
	return 0;
}

function announceWinner(color){
	if(color=="red"){
		$("#playingfield").html("<a style=\"color: red;\">RED PLAYER HAS WON</a>");
	}else if(color=="yellow"){
		$("#playingfield").html("<a style=\"color: yellow;\">YELLOW PLAYER HAS WON</a>");
	}else if(color=="draw"){
		$("#playingfield").html("<a style=\"color: yellow;\">D</a><a style=\"color: red;\">R</a><a style=\"color: yellow;\">A</a><a style=\"color: red;\">W</a>");	
	}
}

function hasPlayerWon(){
	if(isDraw()){announceWinner("draw");blink4(0,0,5)}
	var pl=0;
	for(var i=0;i<6;i++){
		if(pl!=0){break;}
		for(var j=0;j<7;j++){
			if(game.grid[i][j]===0){continue;}
			console.log("testing on "+i+","+j);
			pl = verticalWin(i,j);
			if(pl!=0){blink4(i,j,1);console.log("VW");break;}
			pl = horizontalWin(i,j);
			if(pl!=0){blink4(i,j,2);console.log("HW");break;}
			pl = diagonialWin1(i,j);
			if(pl!=0){blink4(i,j,3);console.log("D1W");break;}
			pl = diagonialWin2(i,j);
			if(pl!=0){blink4(i,j,4);console.log("D2W");break;}
		}
	}

	if(pl==1){
		game.winner=1;
		announceWinner("red");
	}else if(pl==2){
		game.winner=2;
		announceWinner("yellow");
	}
	return 0;
}

function isValidMove(i,j){
	if(game.grid[i][j]==0){
		if(i==5){
			return 1;
		}else if(game.grid[i+1][j]!=0){
			return 1;
		}
	}
	return 0;
}

function editCell(i,j,color){
	var id="#c"+i+"_"+j;

	if(color==="red"){
		$(id).attr("src","red_player.png");
	}else if(color==="yellow"){
		$(id).attr("src","yellow_player.png");
	}
}

function updatePage(){

	$("#emptycells").text(42-game.moves);
	$("#usedcells").text(game.moves);

	if(getPlayerTurn()==1){
		$("#activeplayer").text("RED");
		$("#activeplayer").css("color","red");
	}else{
		$("#activeplayer").text("YELLOW");
		$("#activeplayer").css("color","yellow");
	}

	for(var i=0;i<6;i++){
		for(var j=0;j<7;j++){
			if(game.grid[i][j]==1 ){
				editCell(i,j,"red");
			}else if(game.grid[i][j]==2){
				editCell(i,j,"yellow");
			}
		}
	}
}

function changePlayerTurn(){
	if(getPlayerTurn()==1){
		game.playing=2
		$("#activeplayer").text("YELLOW");
		$("#activeplayer").css("color","yellow");
	}else{
		game.playing=1
		$("#activeplayer").text("RED");
		$("#activeplayer").css("color","red");
	}
}

function play(i,j){
	console.log(game);
	if(game.winner==0){
		if(isValidMove(i,j)){
			game.grid[i][j]=getPlayerTurn();
			game.moves++;

			changePlayerTurn();
			updatePage();
			hasPlayerWon();
			
		}else if(i!=5 && game.grid[i+1][j]==0){
			alert("You can only place tiles on the bottom row, or on top of other tiles");
		}else{
			alert("This position is already taken");
		}
	}
}