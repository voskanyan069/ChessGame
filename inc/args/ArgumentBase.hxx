#ifndef __ARGS_ARGUMENT_BASE_HXX__
#define __ARGS_ARGUMENT_BASE_HXX__

template <typename T>
class CMDArgument;

class ArgumentBase
{
public:
    virtual ~ArgumentBase()
	{
	}

	template <typename T>
    const T& Get() const
	{
		return ((const CMDArgument<T>*)(this))->Get();
	}
};

#endif // __ARGS_ARGUMENT_BASE_HXX__
