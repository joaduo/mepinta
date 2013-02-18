'''
Created on Mar 13, 2012

@author: jduo
'''

class NoConfigError(RuntimeError):
  pass

#TODO: rename to ContextClassConfigWrapper
class ConfigWrapper(object):
  '''
    Provides a wrapper for a context object to have easier access to a
    class' own config.
    This wrapper is used by classes inheriting from 'SelfConfigBase' 
    for reading and writing its own config.
  '''
  def __init__(self,OwnerClass,context):
    object.__setattr__(self,'OwnerClass', OwnerClass)
    object.__setattr__(self,'context', context)
  def __getattr__(self, name):
    #TODO:CODE VALIDATION validate call stack
    if name in ['context','OwnerClass']: #context and OwnerClass shouldn't be intercepted
      object.__getattribute__(self,name)
    elif self.context.has_config(name,self.OwnerClass): #Intercept other config name
      return self.context.get_config(name,self.OwnerClass)
    else: #there is no config for such name
      raise NoConfigError('There is no config for %r of the class %r'%(name,self.OwnerClass))
  def has(self, name):
    try:
      self.__getattr__(name)
      return True
    except NoConfigError:
      return False
  def __setattr__(self, name,value):
    key_names = ['context','OwnerClass']
    if name not in key_names : #context and OwnerClass shouldn't be intercepted
      self.context.set_config(name,value,self.OwnerClass)
    else:
      class_str = "%s.%s"%(self.OwnerClass.__module__.__str__(),self.OwnerClass.__name__)
      raise RuntimeError('You shouldn\'t use the names in %r for a class\' own config. (%r in this case) \n'\
                         'The names in %r are reserved attributes for the context wrapper. Please use any other config name.'% \
                         (key_names,class_str,key_names))

