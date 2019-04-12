#pragma once

#include <boost/wave.hpp>

template<class TBase>
class IBasePreprocessor
{
public:
    typename TBase::context_type TCtx;
    typename TBase::iterator_type TIter;

    IBasePreprocessor(TCtx* ctx = NULL) {}
    virtual ~IBasePreprocessor() {}

    virtual TCtx* context() = 0;
    virtual void set_filename(const std::wstring& fname) = 0;
    virtual void set_rel_filename(const std::wstring& fname) = 0;
    virtual void set_std_filename(const std::wstring& fname) = 0;

    virtual TIter begin() const = 0;
    virtual TIter end() const = 0;
};

template<class TBase>
class Preprocessor
{
public:
    typename TBase::iterator iterator;
    typename TBase::context base_context;

    struct SContext
    {
        SContext(const std::wstring& _fname,
            const std::list<std::wstring>& _dirs,
            base_context* _ctx = NULL)
            : fname(_fname), dirs(_dirs), ctx(_ctx) {};

        std::wstring fname;
        std::list<std::wstring> dirs;
        base_context* ctx;
    };

    Preprocessor(const SContext& context)
        : TBase(toAbsolute(fname), context.ctx),
          m_ctx(context)
    {
        if (m_ctx.ctx == NULL)

    };

    virtual ~Preprocessor() {};

    void recursive(const std::wstring& fname)
    {
        Preprocessor* pp = new Preprocessor(fname, context());
    }

    std::wstring toAbsolute(const std::wstring& fname) const
    {

    }

    Preprocessor::iterator begin() const;
    Preprocessor::iterator end() const;

private:
    SContext m_ctx;
};
