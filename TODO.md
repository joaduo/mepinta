## TODO

1. Simplify design
1. Remove need to pass context on construction (only in python). Shedskin doesn't support custom "with" statement
  1. Make a transition. First support receiving context=, If context is none, then solve it
  1. Then remove context= little by little
1. Remove __post_init__?, although its kind of cool. Should keep it for a while.
    1. Although makes things too implicit?
1. 
1. Remove configuration per class. E.g.: ('non_cached', 'class::mepinta.pipelineview.graph.GraphTopologyManager.GraphTopologyManager'):False
  1. I can leave everything in place, but remove access to it
    so i simply should use self.context.non_cached_evaluation
    or self.config.get('non_cached_evaluation')
1. Most private '__meth' methods should be friend instead '_meth'
