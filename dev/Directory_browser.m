(* ::Package:: *)

SetDirectory[NotebookDirectory[]]


SetDirectory[".."]


load[dir_] := (
	Run["scanDir.exe","\""<>#<>"\"",IntegerString[Hash[#],36],IntegerString[Hash[FileNames["*.big",#]],36]]&[dir];
	With[{strm = OpenRead[FileNameJoin[{Directory[],"cache", IntegerString[Hash[dir],36]}]]},
		ReadList[strm, String, 1];
		Block[{out = ReadList[strm,{Word,Word,Number,Number,Number,Number,Number,Number,Number,Word},WordSeparators->{"\t"}]},
			Close[strm];
			out
		]
	])


SetAttributes[render, HoldAll];
render[preview_, selected_] :=
	Join[{MapThread[Function[{name,num},Button[name,preview=SortBy[preview,#[[num]]&]]],
			{{"Name","Comment","T","AOI","POLA","Scans","Resolution","Min","Max","Range"},Range[10]}]},
		Map[{Button[FileNameTake[#[[1]]],AppendTo[selected,#[[1]]]]}~Join~#[[2;;]]&, preview]] //
	Grid[#, Background -> {{GrayLevel[1], None, GrayLevel[1]},{{GrayLevel[0.85], RGBColor[0.88, 1, 0.88]}}}, Frame -> All]&


SetAttributes[remover,HoldFirst];
remover[list_] := Column@MapIndexed[Button[#,list=Delete[list,First@#2]]&,list]


preload[path_]:=With[{dirs=FileNameJoin[FileNameSplit[path][[;;#]]]&/@Range[Length@FileNameSplit[path]]},
DynamicModule[
	{preview={},selected={},init=Select[#<>":\\"&/@CharacterRange["A","Z"],DirectoryQ],directoryTree,directorySubTree},
	Dynamic[
		Panel[
			Pane[
				Grid[{{
					Pane[Column[directoryTree/@init],{350,Full},Scrollbars->True],
					Pane[Dynamic[render[preview,selected]],{Full,800},Scrollbars->True],
					Dynamic[remover@selected]}}, Alignment->{Left,Top}],
				{Full,800},Scrollbars->{False,True},AppearanceElements->All,BaseStyle->LineBreakWithin->False
			],
			"Viewer"
		],
		UnsavedVariables :> {preview,directoryTree,directorySubTree},
		Initialization :> {
			selected={};
			preview={};
			directoryTree[root_String?DirectoryQ] :=
				DynamicModule[{open=MemberQ[dirs,root],subTree=If[MemberQ[dirs,root],directorySubTree[root],""]},
					PaneSelector[{
						False -> #,
						True -> Column[{#,
							Dynamic[subTree]}]}, Dynamic[open],ImageSize->Automatic] & [
						Row[{
							Opener[Dynamic[open,{Automatic,If[#,subTree=directorySubTree[root],subTree=.]&}]],
							MouseAppearance[EventHandler[
								FileNameTake[root],
								"MouseClicked":>(preview=load[root]),Method->"Queued"],"LinkHand"]
						}]
					]
				];
			directorySubTree[root_String?DirectoryQ] :=
				Module[{subDirs,offset},
					subDirs = Quiet@Check[Select[FileNames["*",root],DirectoryQ],$Failed];
					offset=Grid[{{Invisible@Opener[],#}},Spacings->{0,0}]&;
					offset@Switch[subDirs,
						$Failed,Row[{Style["\[WarningSign]",20]," access denied"},BaseStyle->Orange],
						{},Style["\[FreakedSmiley]",Blue,20],
						_,Column[directoryTree/@Select[FileNames["*",root],DirectoryQ]]]
				]
		}
	]
] ]


CreateDialog[preload[Directory[]]]
