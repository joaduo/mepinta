## TODO

1. Make undoablegraph work
	means working with action tree
	undo-redo things
	plan Schedule For Deletion support? (but not implementing it)
		create action
		alter it
		move around action tree
		delete branch
		copy branch 

1. Implement copy on write for non-cached data (so responsibility is on data's side)
1. Simplify design
1. Remove need to pass context on construction (only in python). Shedskin doesn't support custom "with" statement
  1. Make a transition. First support receiving context=, If context is none, then solve it
  1. Then remove context= little by little
1. Remove __post_init__?, although its kind of cool. Should keep it for a while.
    1. Although makes things too implicit?
1. Remove configuration per class. E.g.: ('non_cached', 'class::mepinta.pipelineview.graph.GraphTopologyManager.GraphTopologyManager'):False
  1. I can leave everything in place, but remove access to it
    so i simply should use self.context.non_cached_evaluation
    or self.config.get('non_cached_evaluation')
1. Most private '__meth' methods should be friend instead '_meth'
1. Support default values when defining processor's manifest
	inputs.name = prop('str', default='my name is', other='...'
	many other options?? warning values? (not now)

1. in python replace?? (SEEMS WORTH ANYWAY!)
	getPropValue(args, 'inputs', 'graph')
	for args.inputs.graph?
	It won't be able to optimize for C++ though!
	nevertheless it won't matter if plugin is python only
	Migrating it won't be that difficult?
	But the point is making pure python plugins a reality!