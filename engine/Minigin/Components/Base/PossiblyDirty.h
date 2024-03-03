#ifndef COMPONENTMEMBER_H
#define COMPONENTMEMBER_H
#include <concepts>
#include <future>
#include <optional>

template<class TFactory, typename TValue, class... TFactoryArgs>
class PossiblyDirty final {
public:
	template<
	        typename = typename std::enable_if<
	                std::is_constructible_v<TFactory> and std::is_invocable_v<TFactory, TFactoryArgs...>>>
	explicit PossiblyDirty(TFactoryArgs... args)
	    : m_Factory{}
	    , m_FactoryArguments{args...} {
		m_ValueCache = std::apply(m_Factory, m_FactoryArguments);
	}

	template<
	        typename = typename std::enable_if<
	                std::is_constructible_v<TFactory> and std::is_invocable_v<TFactory, TFactoryArgs...>>>
	explicit PossiblyDirty(TFactory &&factory, TFactoryArgs... args)
	    : m_Factory{std::move(factory)}
	    , m_FactoryArguments{args...} {
		m_ValueCache = std::apply(m_Factory, m_FactoryArguments);
	}

	[[nodiscard]]
	bool
	operator==(const PossiblyDirty<TValue, TFactory> &other) {
		return m_ValueCache == other.m_Value;
	}

	TValue &operator*() {
		if (m_ValueCache.has_value())
			return m_ValueCache.value();

		m_ValueCache = std::apply(m_Factory, m_FactoryArguments);

		return m_ValueCache.value();
	}

	template<typename = typename std::enable_if<std::is_copy_constructible_v<TValue>>>
	PossiblyDirty &operator=(const TValue &value) {
		m_ValueCache = value;
	}

	template<typename = typename std::enable_if<std::is_move_constructible_v<TValue>>>
	PossiblyDirty &operator=(TValue &&value) {
		m_ValueCache = std::move(value);
	}

	void Update(TFactoryArgs... args) {
		m_FactoryArguments = std::make_tuple(args...);
		m_ValueCache       = std::nullopt;
	}

	template<
	        class... TFactoryCtorArgs,
	        typename = typename std::enable_if<std::is_constructible_v<TFactory, TFactoryCtorArgs &&...>>>
	void InitFactory(TFactoryCtorArgs &&...args) {
		m_Factory    = TFactory{std::forward<TFactoryCtorArgs>(args)...};
		m_ValueCache = std::nullopt;
	}

private:
	std::optional<TValue>       m_ValueCache{};
	TFactory                    m_Factory;
	std::tuple<TFactoryArgs...> m_FactoryArguments;
};

#endif//COMPONENTMEMBER_H
